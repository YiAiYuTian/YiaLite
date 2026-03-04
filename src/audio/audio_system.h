#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "../core/core.h"

#include <string_view>

namespace lite
{

class LITE_API AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    bool addSound(std::string_view name, std::string_view path);
    bool replaceSound(std::string_view name, std::string_view path);
    bool hasSound(std::string_view name) const;
    void removeSound(std::string_view name);
    void removeAllSounds();

    bool playSound(std::string_view path);
    bool playSoundFromName(std::string_view name, bool loop = false, float volume = 1.0f);

    size_t getSoundCount() const;
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif