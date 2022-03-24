#ifndef FLSYSTEM_IPC_H
#define FLSYSTEM_IPC_H

#include "../../../FLSystemConfig.h"
#include "../../Object/FLObject.h"
#include "../../SafeSTL/FLQueue/FLQueue.h"
#include "Event/EventCore/EventCore.h"
#include "Event/FLEvent/FLEvent.h"

namespace FLSYSTEM
{
    class IPC : public FLObject
    {
    private:

    public:
        IPC();
        virtual ~IPC();
        static EventCore eventCore;
        void begin() {}
        void run() { eventCore.process(); }
    };
}

#define FLEventCore (FLSYSTEM::IPC::eventCore)

#endif