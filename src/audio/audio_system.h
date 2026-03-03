#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "../core/core.h"

#include <string_view>

namespace lite
{

class LITE_API AudioSystem
{
public:
    AudioSystem();
    ~AudioSystem();

    bool addSoundToSystem(std::string_view name, std::string_view path);
    void removeSoundFromSystem(std::string_view name);

    bool playSound(std::string_view path);
    bool playSoundFromName(std::string_view name);

    size_t getSoundCount() const;
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif