#ifndef EVENT_H
#define EVENT_H

#include "../core/core.h"

namespace lite
{

class LITE_API Event
{
public:
    Event();
    ~Event();

    void onUpdate();
    bool is_running = true;
private:
    struct Impl;
    Impl* m_impl;
};

}

#endif