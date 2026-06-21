#ifndef YIALITE_AUDIO_MANAGER_H
#define YIALITE_AUDIO_MANAGER_H

#include "../core/core.h"
#include "../core/result.h"

namespace yialite
{

class YIALITE_API AudioManager
{
public:
    ~AudioManager();
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&& other) noexcept;
    AudioManager& operator=(AudioManager&& other) noexcept;

    static Result<AudioManager*> create();
    static void destroy(AudioManager* manager);

    Result<void> add_sound(const char* name, const char* path);
    Result<void> replace_sound(const char* name, const char* path);
    bool has_sound(const char* name) const;
    Result<void> remove_sound(const char* name);
    void remove_all_sounds();

    Result<void> play_sound(const char* path);
    Result<void> play_sound_from_name(const char* name, bool loop = false, float volume = 1.0f);

    size_t get_sound_count() const;

    explicit operator bool() const noexcept { return m_impl != nullptr; }
private:
    AudioManager() = default;
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif
