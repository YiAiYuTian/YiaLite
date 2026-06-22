#include "pch.h"
#include "audio_manager.h"
#include "../core/error.h"
#include "../core/logger.h"
#include "../utils/memory/allocator.h"
#include "../utils/containers/yia_hashmap.h"
#include "../utils/string/yia_string.h"

#include <miniaudio_libvorbis.h>

namespace yialite
{

void* yialite_miniaudio_malloc(size_t sz, void* pUserData)
{
    return ALLOCATE_SIZED(sz);
}

void* yialite_miniaudio_realloc(void *p, size_t sz, void *pUserData)
{
    return REALLOCATE_SIZED(p, sz);
}

void yialite_miniaudio_free(void *p, void *pUserData)
{
    DEALLOCATE(p);
}

struct AudioManager::Impl
{
    ma_engine engine;
    ma_resource_manager resource_manager;
    HashMap<String, ma_sound*> sounds;
};

AudioManager::AudioManager(AudioManager&& other) noexcept
    : m_impl(other.m_impl)
{
    other.m_impl = nullptr;
}

AudioManager& AudioManager::operator=(AudioManager&& other) noexcept
{
    if (this != &other)
    {
        if (m_impl)
        {
            for (auto pair : m_impl->sounds)
            {
                ma_sound_uninit(pair.second);
                DEALLOCATE(pair.second);
            }
            m_impl->sounds.clear();
            ma_engine_uninit(&m_impl->engine);
            ma_resource_manager_uninit(&m_impl->resource_manager);
            DEALLOCATE_OBJECT(AudioManager::Impl, m_impl);
        }
        m_impl = other.m_impl;
        other.m_impl = nullptr;
    }
    return *this;
}

Result<AudioManager*> AudioManager::create()
{
    AudioManager* am = ALLOCATE_OBJECT(AudioManager);
    am->m_impl = ALLOCATE_OBJECT(AudioManager::Impl);

    ma_result result;
    ma_resource_manager_config resource_manager_config;
    ma_engine_config engine_config;

    ma_decoding_backend_vtable* pCustomBackendVTables[] = {
        ma_decoding_backend_libvorbis,
        nullptr
    };

    resource_manager_config = ma_resource_manager_config_init();
    resource_manager_config.ppCustomDecodingBackendVTables = pCustomBackendVTables;
    resource_manager_config.customDecodingBackendCount     = sizeof(pCustomBackendVTables) / sizeof(pCustomBackendVTables[0]);
    resource_manager_config.pCustomDecodingBackendUserData = nullptr;

    result = ma_resource_manager_init(&resource_manager_config, &am->m_impl->resource_manager);
    if (result != MA_SUCCESS)
    {
        DEALLOCATE_OBJECT(AudioManager::Impl, am->m_impl);
        am->m_impl = nullptr;
        DEALLOCATE_OBJECT(AudioManager, am);
        return Result<AudioManager*>(ErrorCode::AudioEngineInitFailed, ma_result_description(result));
    }

    engine_config = ma_engine_config_init();
    engine_config.pResourceManager = &am->m_impl->resource_manager;
    engine_config.allocationCallbacks.onMalloc   = yialite_miniaudio_malloc;
    engine_config.allocationCallbacks.onRealloc  = yialite_miniaudio_realloc;
    engine_config.allocationCallbacks.onFree     = yialite_miniaudio_free;

    result = ma_engine_init(&engine_config, &am->m_impl->engine);
    if (result != MA_SUCCESS)
    {
        ma_resource_manager_uninit(&am->m_impl->resource_manager);
        DEALLOCATE_OBJECT(AudioManager::Impl, am->m_impl);
        am->m_impl = nullptr;
        DEALLOCATE_OBJECT(AudioManager, am);
        return Result<AudioManager*>(ErrorCode::AudioEngineInitFailed, ma_result_description(result));
    }

    Logger::info("AudioManager initialized successfully");
    return am;
}

AudioManager::~AudioManager()
{
    if (!m_impl) return;

    for (auto pair : m_impl->sounds)
    {
        ma_sound_uninit(pair.second);
        DEALLOCATE(pair.second);
    }
    m_impl->sounds.clear();

    ma_engine_uninit(&m_impl->engine);
    ma_resource_manager_uninit(&m_impl->resource_manager);
    DEALLOCATE_OBJECT(AudioManager::Impl, m_impl);
    m_impl = nullptr;
}

void AudioManager::destroy(AudioManager* manager)
{
    DEALLOCATE_OBJECT(AudioManager, manager);
}

Result<void> AudioManager::add_sound(const char* name, const char* path)
{
    ma_result result;
    String sound_name(name);
    ma_sound* sound = nullptr;

    sound = ALLOCATE(ma_sound);

    result = ma_sound_init_from_file(&m_impl->engine, path, 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
    {
        DEALLOCATE(sound);
        return Result<void>(ErrorCode::SoundLoadFailed, ma_result_description(result));
    }

    m_impl->sounds.emplace(yialite::move(sound_name), yialite::move(sound));
    return ok();
}

Result<void> AudioManager::replace_sound(const char* name, const char* path)
{
    String key(name);
    if (auto value = m_impl->sounds.find(key); value)
    {
        ma_sound_uninit(*value);
        DEALLOCATE(*value);
        m_impl->sounds.remove(key);
        return add_sound(name, path);
    }
    return Result<void>(ErrorCode::SoundNotFound, "Sound '" + String(name) + "' not found, replace failed");
}

Result<void> AudioManager::remove_sound(const char* name)
{
    String key(name);
    if (auto value = m_impl->sounds.find(key); value)
    {
        ma_sound_uninit(*value);
        DEALLOCATE(*value);
        m_impl->sounds.remove(key);
        return ok();
    }
	return Result<void>(ErrorCode::SoundNotFound, "Sound '" + String(name) + "' not found, remove failed");
}

void AudioManager::remove_all_sounds()
{
    for (auto pair : m_impl->sounds)
    {
        ma_sound_uninit(pair.second);
        DEALLOCATE(pair.second);
    }
    m_impl->sounds.clear();
}

bool AudioManager::has_sound(const char* name) const
{
    return m_impl->sounds.find(String(name), nullptr);
}

Result<void> AudioManager::play_sound(const char* path)
{
    ma_result result;
    result = ma_engine_play_sound(&m_impl->engine, path, nullptr);
    if (result != MA_SUCCESS)
    {
        return Result<void>(ErrorCode::SoundPlayFailed, "Failed to play sound '" + String(path) + "' :" + ma_result_description(result));
    }
    return ok();
}

Result<void> AudioManager::play_sound_from_name(const char* name, bool loop, float volume)
{
    String key(name);
    if (auto value = m_impl->sounds.find(key); value)
    {
        ma_result result;
        if (loop) ma_sound_set_looping(*value, MA_TRUE);
        volume = std::clamp(volume, 0.0f, 1.0f);
        ma_sound_set_volume(*value, volume);

        result = ma_sound_start(*value);
        if (result != MA_SUCCESS)
        {
			return Result<void>(ErrorCode::SoundPlayFailed, "Failed to play sound '" + String(name) + "' :" + ma_result_description(result));
        }
        return ok();
    }

    return Result<void>(ErrorCode::SoundNotFound, "Sound '" + String(name) + "' not found");
}

size_t AudioManager::get_sound_count() const
{
    return m_impl->sounds.size();
}

}
