#include "audio_manager.h"
#include "../core/yialite_exception.h"
#include "../core/logger.h"
#include "../utils/memory/allocator.h"
#include "../utils/containers/yia_hashmap.h"
#include "../utils/string/yia_string.h"

#include <miniaudio.h>
#include "../thirdparty/miniaudio/libvorbis/miniaudio_libvorbis.h"
#include <unordered_map>
#include <string>

namespace yialite
{

void* yialiteMiniAudioMalloc(size_t sz, void* pUserData)
{
    return ALLOCATE_SIZED(sz);
}

void* yialiteMiniAudioRealloc(void *p, size_t sz, void *pUserData)
{
    return REALLOCATE_SIZED(p, sz);
}

void yialiteMiniAudioFree(void *p, void *pUserData)
{
    DEALLOCATE(p);
}

struct AudioManager::Impl
{
    ma_engine engine;
    ma_resource_manager resource_manager;
    HashMap<String, ma_sound*> sounds;
};

AudioManager::AudioManager()
{
    m_impl = ALLOCATE_OBJECT(AudioManager::Impl);

    ma_result result;
    ma_resource_manager_config resourceManagerConfig;
    ma_engine_config engineConfig;

    ma_decoding_backend_vtable* pCustomBackendVTables[] = {
        ma_decoding_backend_libvorbis,
        NULL
    };

    resourceManagerConfig = ma_resource_manager_config_init();
    resourceManagerConfig.ppCustomDecodingBackendVTables = pCustomBackendVTables;
    resourceManagerConfig.customDecodingBackendCount     = sizeof(pCustomBackendVTables) / sizeof(pCustomBackendVTables[0]);
    resourceManagerConfig.pCustomDecodingBackendUserData = nullptr;

    result = ma_resource_manager_init(&resourceManagerConfig, &m_impl->resource_manager);
    if (result != MA_SUCCESS)
        throw YiaLite_Exception("Failed to initialize ma resource manager: " + String(ma_result_description(result)));

    engineConfig = ma_engine_config_init();
    engineConfig.pResourceManager = &m_impl->resource_manager;
    engineConfig.allocationCallbacks.onMalloc   = yialiteMiniAudioMalloc;
    engineConfig.allocationCallbacks.onRealloc  = yialiteMiniAudioRealloc;
    engineConfig.allocationCallbacks.onFree     = yialiteMiniAudioFree;

    result = ma_engine_init(&engineConfig, &m_impl->engine);
    if (result != MA_SUCCESS)
        throw YiaLite_Exception("Failed to initialize engine: " + String(ma_result_description(result)));

    Logger::info("AudioManager initialized successfully");
}

AudioManager::~AudioManager()
{
    for(auto pair : m_impl->sounds)
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

bool AudioManager::addSound(const char* name, const char* path)
{
    ma_result result;
    String sound_name(name);
    ma_sound* sound = nullptr;

    sound = ALLOCATE(ma_sound);

    result = ma_sound_init_from_file(&m_impl->engine, path, 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
    {
        DEALLOCATE(sound);
        return false;
    }

    m_impl->sounds.emplace(yialite::move(sound_name), yialite::move(sound));
    Logger::info("Sound '{}' added to system", name);
    return true;
}

bool AudioManager::replaceSound(const char* name, const char* path)
{
    String key(name);
    if(auto value = m_impl->sounds.find(key); value)
    {
        ma_sound_uninit(*value);
        DEALLOCATE(*value);
        m_impl->sounds.remove(key);
        return addSound(name, path);
    }
    Logger::warn("Sound '{}' not found, replace failed", name);
    return false;
}

void AudioManager::removeSound(const char* name)
{
    String key(name);
    if(auto value = m_impl->sounds.find(key); value)
    {
        ma_sound_uninit(*value);
        DEALLOCATE(*value);
        m_impl->sounds.remove(key);
        Logger::info("Sound '{}' removed from system", key);
        return;
    }
    Logger::warn("Sound '{}' not found, remove failed", key);
}

void AudioManager::removeAllSounds()
{
    for(auto pair : m_impl->sounds)
    {
        ma_sound_uninit(pair.second);
        DEALLOCATE(pair.second);
    }
    m_impl->sounds.clear();
}

bool AudioManager::hasSound(const char* name) const
{
    return m_impl->sounds.find(String(name), nullptr);
}

bool AudioManager::playSound(const char* path)
{
    ma_result result;
    result = ma_engine_play_sound(&m_impl->engine, path, nullptr);
    if(result != MA_SUCCESS)
    {
        Logger::error("Failed to play sound '{}': {}", path, ma_result_description(result));
        return false;
    }
    return true;
}

bool AudioManager::playSoundFromName(const char* name, bool loop, float volume)
{
    String key(name);
    if(auto value = m_impl->sounds.find(key); value)
    {
        ma_result result;
        if(loop) ma_sound_set_looping(*value, MA_TRUE);
        volume = std::clamp(volume, 0.0f, 1.0f);
        ma_sound_set_volume(*value, volume);

        result = ma_sound_start(*value);
        if(result != MA_SUCCESS)
        {
            Logger::error("Failed to play sound '{}': {}", name, ma_result_description(result));
            return false;
        }
        return true;
    }

    Logger::warn("Sound '{}' not found", name);
    return false;
}

size_t AudioManager::getSoundCount() const
{
    return m_impl->sounds.size();
}

}