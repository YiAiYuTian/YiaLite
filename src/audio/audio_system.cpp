#include "audio_system.h"
#include "../core/lite_exception.h"
#include "../core/log.h"

#include <miniaudio.h>
#include "miniaudio/libvorbis/miniaudio_libvorbis.h"
#include <unordered_map>
#include <string>

namespace lite
{

struct AudioManager::Impl
{
    ma_engine* engine = nullptr;
    ma_resource_manager* resource_manager = nullptr;
    std::unordered_map<std::string, ma_sound*> sounds;
};

AudioManager::AudioManager()
{
    m_impl = new Impl();
    m_impl->engine = new ma_engine();
    m_impl->resource_manager = new ma_resource_manager();

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

    result = ma_resource_manager_init(&resourceManagerConfig, m_impl->resource_manager);
    if (result != MA_SUCCESS)
        throw Lite_Exception("Failed to initialize ma resource manager: " + std::string(ma_result_description(result)));

    engineConfig = ma_engine_config_init();
    engineConfig.pResourceManager = m_impl->resource_manager;

    result = ma_engine_init(&engineConfig, m_impl->engine);
    if (result != MA_SUCCESS)
        throw Lite_Exception("Failed to initialize engine: " + std::string(ma_result_description(result)));

    LOG_INFO("AudioManager initialized successfully");
}

AudioManager::~AudioManager()
{
    for(auto& pair : m_impl->sounds)
    {
        ma_sound_uninit(pair.second);
        delete pair.second;
    }
    m_impl->sounds.clear();
    
    ma_engine_uninit(m_impl->engine);
    ma_resource_manager_uninit(m_impl->resource_manager);
    delete m_impl->engine;
    delete m_impl->resource_manager;
    delete m_impl;
}

bool AudioManager::addSound(std::string_view name, std::string_view path)
{
    ma_result result;
    std::string sound_name(name);
    ma_sound* sound = nullptr;

    try
    {
        sound = new ma_sound();
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("{}", e.what());
        return false;
    }

    result = ma_sound_init_from_file(m_impl->engine, path.data(), 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
    {
        delete sound;
        return false;
    }

    auto [it, inserted] = m_impl->sounds.emplace(sound_name, sound);
    if (!inserted) 
    {
        ma_sound_uninit(sound);
        delete sound;
        LOG_WARN("Sound '{}' already exists, insert failed", sound_name);
        return false;
    }

    LOG_INFO("Sound '{}' added to system", sound_name);
    return true;
}

bool AudioManager::replaceSound(std::string_view name, std::string_view path)
{
    if(auto it = m_impl->sounds.find(std::string(name)); it != m_impl->sounds.end())
    {
        ma_sound_uninit(it->second);
        delete it->second;
        m_impl->sounds.erase(it);
        return addSound(name, path);
    }
    LOG_WARN("Sound '{}' not found, replace failed", name.data());
    return false;
}

void AudioManager::removeSound(std::string_view name)
{
    std::string sound_name(name);
    if(auto it = m_impl->sounds.find(sound_name); it != m_impl->sounds.end())
    {
        ma_sound_uninit(it->second);
        delete it->second;
        m_impl->sounds.erase(it);
        LOG_INFO("Sound '{}' removed from system", sound_name);
        return;
    }
    LOG_WARN("Sound '{}' not found, remove failed", sound_name);
}

void AudioManager::removeAllSounds()
{
    for(auto& pair : m_impl->sounds)
    {
        ma_sound_uninit(pair.second);
        delete pair.second;
    }
    m_impl->sounds.clear();
}

bool AudioManager::hasSound(std::string_view name) const
{
    return m_impl->sounds.find(std::string(name)) != m_impl->sounds.end();
}

bool AudioManager::playSound(std::string_view path)
{
    ma_result result;
    result = ma_engine_play_sound(m_impl->engine, path.data(), nullptr);
    if(result != MA_SUCCESS)
    {
        LOG_ERROR("Failed to play sound '{}': {}", path.data(), ma_result_description(result));
        return false;
    }
    return true;
}

bool AudioManager::playSoundFromName(std::string_view name, bool loop, float volume)
{
    if(auto it = m_impl->sounds.find(std::string(name)); it != m_impl->sounds.end())
    {
        ma_result result;
        if(loop) ma_sound_set_looping(it->second, MA_TRUE);
        volume = std::clamp(volume, 0.0f, 50.0f);
        ma_sound_set_volume(it->second, volume);

        result = ma_sound_start(it->second);
        if(result != MA_SUCCESS)
        {
            LOG_ERROR("Failed to play sound '{}': {}", name.data(), ma_result_description(result));
            return false;
        }
        return true;
    }

    LOG_WARN("Sound '{}' not found", name.data());
    return false;
}

size_t AudioManager::getSoundCount() const
{
    return m_impl->sounds.size();
}

}