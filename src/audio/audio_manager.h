#ifndef YIALITE_AUDIO_MANAGER_H
#define YIALITE_AUDIO_MANAGER_H

#include "../core/core.h"

#include <string_view>

namespace yialite
{

class YIALITE_API AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    bool addSound(const char* name, const char* path);
    bool replaceSound(const char* name, const char* path);
    bool hasSound(const char* name) const;
    void removeSound(const char* name);
    void removeAllSounds();

    bool playSound(const char* path);
    bool playSoundFromName(const char* name, bool loop = false, float volume = 1.0f);

    size_t getSoundCount() const;
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif