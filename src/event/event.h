#ifndef EVENT_H
#define EVENT_H

#include "../core/core.h"
#include "keycode.h"

#include <stdint.h>

namespace lite
{

typedef uint32_t Keycode;
typedef uint16_t Keymod;

typedef void (*QuitEventCallback)(void* data);
typedef void (*KeyEventCallback)(Keycode keycode, bool repeat, bool down, Keymod keymod, void* data);

class LITE_API Event
{
public:
    Event();
    ~Event();

    void onUpdate();

    void setGlobalData(void* data);
    void registerQuitEventCallback(QuitEventCallback callback);
    void registerKeyEventCallback(KeyEventCallback callback);
private:
    struct Impl;
    Impl* m_impl;
};

}

#endif