#ifndef YIALITE_AUDIO_ADAPTER_H
#define YIALITE_AUDIO_ADAPTER_H

#include "audio_types.h"
#include "../core/result.h"

namespace yialite
{

class IAudioAdapter
{
public:
    IAudioAdapter() = default;
    virtual ~IAudioAdapter() = default;
    IAudioAdapter(IAudioAdapter&&) = delete;
    IAudioAdapter(const IAudioAdapter&) = delete;
    
    //operators
    IAudioAdapter& operator=(IAudioAdapter&&) = delete;
    IAudioAdapter& operator=(const IAudioAdapter&) = delete;

    //tools
    virtual Result<void> init() = 0;
    virtual void destroy() = 0;
    virtual void update(float dt) = 0;

    virtual SoundID load_sound(const char* path) = 0;
    virtual void unload_sound(SoundID id) = 0;
    virtual void unload_all_sounds() = 0;
    virtual bool is_sound_loaded(SoundID id) const = 0;

    virtual VoiceID play(SoundID id, const PlayParams& params) = 0;
    virtual void stop(VoiceID voice) = 0;
    virtual void stop_all_voices() = 0;
    virtual void pause(VoiceID voice) = 0;
    virtual void resume(VoiceID voice) = 0;
    virtual bool is_voice_playing(VoiceID voice) const = 0;

    virtual void set_volume(VoiceID voice, float v) = 0;
    virtual void set_pitch(VoiceID voice, float v) = 0;
    virtual void set_pan(VoiceID voice, float v) = 0;
    virtual void set_loop(VoiceID voice, bool loop) = 0;

    virtual void set_spatialization(VoiceID voice, bool enabled) = 0;
    virtual void set_voice_position(VoiceID voice, float x, float y, float z) = 0;
    virtual void set_voice_velocity(VoiceID voice, float x, float y, float z) = 0;
    virtual void set_voice_distance(VoiceID voice, float min_dist, float max_dist) = 0;

    virtual void fade_out_and_stop(VoiceID voice, float seconds) = 0;

    virtual void create_bus(const char* name) = 0;
    virtual void set_bus_volume(const char* name, float v) = 0;
    virtual void pause_bus(const char* name) = 0;
    virtual void resume_bus(const char* name) = 0;
    virtual void remove_bus(const char* name) = 0;

    virtual void set_listener(const ListenerState& state) = 0;
    virtual void set_doppler_factor(float factor) = 0;
    virtual void set_speed_of_sound(float speed) = 0;

    virtual size_t get_sound_count() const = 0;
    virtual size_t get_voice_count() const = 0;
};

}

#endif