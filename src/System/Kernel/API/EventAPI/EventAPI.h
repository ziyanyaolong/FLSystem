#ifndef FLSYSTEM_EVENTAPI_H
#define FLSYSTEM_EVENTAPI_H

#include "../../Arch/Object/FLObject.h"
#include "../../Arch/SafeSTL/FLQueue/FLQueue.h"

namespace FLSYSTEM
{
    class FLEvent;
    class EventAPI : public FLObject
    {
    public:
        friend class EventCore;
        struct EventTable
        {
            FLObject* object = nullptr;
            FLEvent* event = nullptr;
        };

    private:
        FLQueue<EventTable*> eventQueue;

    protected:
        virtual void process() = 0;

    public:
        explicit EventAPI(FLObject* parent = nullptr, const std::string& name = std::string("")) : FLObject(parent, name) {}
        EventAPI(const std::string& name) : FLObject(name) {}

        virtual ~EventAPI()
        {
            eventQueue.clear();
        }
    };
}

#endif