#ifndef YIALITE_AUDIO_TYPES_H
#define YIALITE_AUDIO_TYPES_H

#include "../utils/base_types.h"
#include "../utils/handle.h"

namespace yialite
{

struct SoundTag;
using SoundID = Handle<Uint64, SoundTag>;
inline constexpr SoundID INVALID_SOUND_ID = SoundID(0);

struct VoiceID
{
    Uint64 index;
    Uint64 gen;

    static constexpr VoiceID invalid()
    {
        return { Uint64(-1), 0 };
    }

    bool operator==(const VoiceID& other) const
    {
        return index == other.index && gen == other.gen;
    }
    bool operator!=(const VoiceID& other) const
    {
        return !(*this == other);
    }
};
constexpr VoiceID INVALID_VOICE_ID = VoiceID::invalid();

struct PlayParams
{
    const char* bus = "master";
    bool  loop        = false;
    float volume      = 1.0f;
    float pitch       = 1.0f;
    float pan         = 0.0f;
    bool  spatial     = false;
    float x           = 0.0f;
    float y           = 0.0f;
    float z           = 0.0f;
    float min_distance = 1.0f;
    float max_distance = 100.0f;
    float fade_in_time = 0.0f;
};

struct ListenerState
{
    float x          = 0.0f, y          = 0.0f, z          =  0.0f;
    float forward_x  = 0.0f, forward_y  = 0.0f, forward_z  = -1.0f;
    float up_x       = 0.0f, up_y       = 1.0f, up_z       =  0.0f;
    float velocity_x = 0.0f, velocity_y = 0.0f, velocity_z =  0.0f;
};

}

#endif