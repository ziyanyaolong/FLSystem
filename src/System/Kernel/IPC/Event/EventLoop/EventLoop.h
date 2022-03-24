#ifndef FLSYSTEM_EVENTLOOP_H
#define FLSYSTEM_EVENTLOOP_H

#include "../../../../../FLSystemConfig.h"
#include "../EventCore/EventCore.h"
#include "../FLEvent/FLEvent.h"

namespace FLSYSTEM
{
    class EventLoop : public EventCore
    {
    private:
    public:
        EventLoop();
        virtual ~EventLoop();
    };
}

#endif