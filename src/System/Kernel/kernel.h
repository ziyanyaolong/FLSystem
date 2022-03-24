#ifndef FLSYSTEM_KERNEL_H
#define FLSYSTEM_KERNEL_H

#include "ProcessManagement/ProcessSchedule/ProcessSchedule.h"
#include "IPC/IPC.h"

namespace FLSYSTEM
{
    class Kernel
    {
    private:
        
    public:
        Kernel();
        virtual ~Kernel();
        static ProcessSchedule processSchedule;
        static IPC ipc;
        void init();
        void run();
    };
}

#endif