#ifndef FLSYSTEM_PROCESSPOOL_H
#define FLSYSTEM_PROCESSPOOL_H

#include "../../API/ProcessScheduleAPI/ProcessScheduleAPI.h"
#include "../../API/ThreadAPI/ThreadAPI.h"
#include "../../Arch/SafeSTL/FLMap/FLMap.h"
#include "../../Arch/SafeSTL/FLVector/FLVector.h"

#define FLSYSTEM_3RD_ALGORITHM

#include "../../../../PlatformInterface/3rdInclude.h"
#include "../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
	class ProcessPool : public GC_API
	{
	private:
		friend class ProcessSchedule;
		FLMap<uint64_t, ProcessScheduleAPI *>* pool;
		FLVector<ThreadAPI *>* threadPool;
		int64_t maxPID = 1;

	public:
		explicit ProcessPool();
		virtual ~ProcessPool();
		bool addThread(ThreadAPI* thread);
		bool deleteThread(ThreadAPI* thread);

		bool addProcess(ProcessScheduleAPI* process);
		bool deleteProcess(ProcessScheduleAPI* process);

		FLInline unsigned long long getMaxPID()
		{
			return maxPID;
		}
	};
}
#endif