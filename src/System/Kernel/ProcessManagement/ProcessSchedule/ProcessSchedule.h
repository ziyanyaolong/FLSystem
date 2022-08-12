#ifndef FLSYSTEM_PROCESSSCHEDULE_H
#define FLSYSTEM_PROCESSSCHEDULE_H

#include "../../../../PlatformInterface/PlatformInterface.h"
#include "../../API/ProcessScheduleAPI/ProcessScheduleAPI.h"
#include "../../API/ThreadAPI/ThreadAPI.h"
#include "../ProcessPool/ProcessPool.h"
#include "../../IPC/Lock/FLAtomicLock_Bool/FLAtomicLock_Bool.h"
#include "../../API/KernelAPI/KernelAPI.h"
#include "../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
    class ProcessSchedule : public KernelAPI<ProcessSchedule>, public GC_API
    {
    private:
        FLLock* createThreadLock = nullptr;
        ProcessPool* processPool = nullptr;

        static void _runMiddle_T(void *thread);
        static void _runMiddle_P(void *process);

    public:
        int createProcess(ProcessScheduleAPI *process);
        int createThread(ThreadAPI *process);

		void deleteProcess(ProcessScheduleAPI* process);
		void deleteThread(ThreadAPI* process);

        virtual void init() override;
        virtual void run() override;
        virtual bool load() override;

        explicit ProcessSchedule();
        virtual ~ProcessSchedule();
    };
}

#endif