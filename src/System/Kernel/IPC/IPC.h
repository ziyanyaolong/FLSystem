#ifndef FLSYSTEM_IPC_H
#define FLSYSTEM_IPC_H

#include "../../../FLSystemConfig.h"
#include "../API/KernelAPI/KernelAPI.h"
#include "../Arch/SafeSTL/FLQueue/FLQueue.h"
#include "Event/EventCore/EventCore.h"
#include "Event/FLEvent/FLEvent.h"
#include "../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
    class IPC : public KernelAPI<IPC>, public GC_API
    {
    private:

    public:
        explicit IPC();
        virtual ~IPC();
        static EventCore* eventCore;
        virtual void init() override;
        virtual void run() override;
        virtual bool load() override;
    };
}

#define FLEventCore (FLSYSTEM::IPC::eventCore)

#endif