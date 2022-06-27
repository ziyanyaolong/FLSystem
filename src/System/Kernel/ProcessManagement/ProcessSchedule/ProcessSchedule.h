#ifndef FLSYSTEM_PROCESSSCHEDULE_H
#define FLSYSTEM_PROCESSSCHEDULE_H

#include "../../../../PlatformInterface/PlatformInterface.h"
#include "../../API/ProcessScheduleAPI/ProcessScheduleAPI.h"
#include "../../API/ThreadAPI/ThreadAPI.h"
#include "../ProcessPool/ProcessPool.h"
#include "../../IPC/Lock/FLAtomicLock_Bool/FLAtomicLock_Bool.h"

namespace FLSYSTEM
{
    class ProcessSchedule
    {
    private:
        friend class Kernel;
        FLLock createThreadLock;
        static ProcessPool processPool;
        static void _runMiddle_T(void *thread);
        static void _runMiddle_P(void *process);

    public:
        int createProcess(ProcessScheduleAPI *process);
        int createThread(ThreadAPI *process);

        void begin();
        void run();

        ProcessSchedule();
        virtual ~ProcessSchedule();
    };
}

#endif