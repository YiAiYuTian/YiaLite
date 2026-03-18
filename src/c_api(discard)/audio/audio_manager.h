#ifndef C_YIALITE_AUDIO_MANAGER_H
#define C_YIALITE_AUDIO_MANAGER_H

#include "../../cpp_api/core/core.h"

#include <stdbool.h>

typedef struct YiaLite_AudioManager YiaLite_AudioManager;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API YiaLite_AudioManager* YiaLite_CreateAudioManager();
YIALITE_API void YiaLite_DestroyAudioManager(YiaLite_AudioManager* audio_manager);

YIALITE_API bool YiaLite_AddSound           (YiaLite_AudioManager* audio_manager, const char* name, const char* path);
YIALITE_API bool YiaLite_ReplaceSound       (YiaLite_AudioManager* audio_manager, const char* name, const char* path);
YIALITE_API bool YiaLite_HasSound           (YiaLite_AudioManager* audio_manager, const char* name);
YIALITE_API void YiaLite_RemoveSound        (YiaLite_AudioManager* audio_manager, const char* name);
YIALITE_API void YiaLite_RemoveAllSounds    (YiaLite_AudioManager* audio_manager);

YIALITE_API bool YiaLite_PlaySound          (YiaLite_AudioManager* audio_manager, const char* path);
YIALITE_API bool YiaLite_PlaySoundFromName  (YiaLite_AudioManager* audio_manager, const char* name, bool loop, float volume);

YIALITE_API size_t YiaLite_GetSoundCount    (YiaLite_AudioManager* audio_manager);

#ifdef __cplusplus
}
#endif

#endif