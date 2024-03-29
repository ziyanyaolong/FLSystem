#ifndef FLSYSTEM_EVENTCORE_H
#define FLSYSTEM_EVENTCORE_H

#include "../../../../../PlatformInterface/PlatformInterface.h"
#include "../../../API/EventAPI/EventAPI.h"
#include "../../../Arch/SafeSTL/FLQueue/FLQueue.h"
#include "../FLEvent/FLEvent.h"

namespace FLSYSTEM
{
    class EventCore : public EventAPI
    {
    public:
        friend class EventMain;

    protected:
        static EventTable *condense(EventAPI* eventAPI, std::size_t number = 0);

    public:
        explicit EventCore();
        virtual ~EventCore();

        static void process(EventAPI* eventAPI);

        static bool notify(FLObject *object, FLEvent *event);

        static bool sendEvent(FLObject *receiver, FLEvent *event);
        static bool postEvent(FLObject *receiver, FLEvent *event);

        FLInline virtual void process() override { EventCore::process(static_cast<EventAPI*>(this)); }
    };
}

#endif