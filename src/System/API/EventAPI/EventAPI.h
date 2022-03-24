#ifndef FLSYSTEM_EVENTAPI_H
#define FLSYSTEM_EVENTAPI_H

#include "../../Object/FLObject.h"
#include "../../SafeSTL/FLQueue/FLQueue.h"

namespace FLSYSTEM
{
    class FLEvent;
    class EventAPI : public FLObject
    {
    public:
        friend class EventCore;
        struct EventTable
        {
            FLObject *object = nullptr;
            FLEvent *event = nullptr;
        };

    private:
        FLQueue<EventTable *> eventQueue;
        //std::atomic_bool isLoop;
        //std::atomic_bool isEndLoop;

    protected:
        virtual void process() = 0;

    public:
        explicit EventAPI(FLObject *parent = nullptr, const std::string &name = std::string("")) : FLObject(parent, name) {}
        EventAPI(const std::string &name) : FLObject(name) {}

        virtual ~EventAPI()
        {
            eventQueue.clear();
        }

        virtual void exec()
        {
            //isEndLoop.store(false);
            //isLoop.store(true);
            //while (isLoop.load())
            //{
            //    process();
            //    FLTaskDelay(10);
            //}
            //isEndLoop.store(true);
        }

        void exit()
        {
            //isLoop.store(false);
        }
    };
}

#endif