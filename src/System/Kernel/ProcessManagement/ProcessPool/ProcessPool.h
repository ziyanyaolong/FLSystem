#ifndef FLSYSTEM_PROCESSPOOL_H
#define FLSYSTEM_PROCESSPOOL_H

#include "../../../API/ProcessScheduleAPI/ProcessScheduleAPI.h"
#include "../../../API/ThreadAPI/ThreadAPI.h"
#include "../../../SafeSTL/FLMap/FLMap.h"
#include "../../../SafeSTL/FLVector/FLVector.h"

namespace FLSYSTEM
{
	class ProcessPool
	{
	private:
		friend class ProcessSchedule;
		FLMap<uint64_t, ProcessScheduleAPI *> pool;
		FLVector<ThreadAPI *> threadPool;
		int64_t maxPID = 1;

	public:
		ProcessPool();
		virtual ~ProcessPool();
		bool addThread(ThreadAPI *thread)
		{
			if (thread == nullptr)
			{
				return false;
			}

			threadPool.lock();
			if (std::find(threadPool.begin(), threadPool.end(), thread) != threadPool.end())
			{
				threadPool.unlock();
				return false;
			}
			threadPool.unlock();

			threadPool.push_back(thread);
			return true;
		}
		bool deleteThread(ThreadAPI *thread)
		{
			if (thread == nullptr)
			{
				return false;
			}

			threadPool.lock();
			auto it = std::find(threadPool.begin(), threadPool.end(), thread);
			if (it == threadPool.end())
			{
				threadPool.unlock();
				return false;
			}
			threadPool.unlock();

			threadPool.erase(it);
			return true;
		}
		bool addProcess(ProcessScheduleAPI *process)
		{
			if (process == nullptr)
			{
				return false;
			}

			if (process->processConfig.PID != 0 || !(addThread(process)))
			{
				return false;
			}

			bool isAdd = false;
			pool.lock();
			for (auto i = pool.begin(); i != pool.end(); i++)
			{
			    if (i->second == nullptr)
			    {
			        process->processConfig.PID = i->first;
			        i->second = process;
			        isAdd = true;
			    }
			}
			
			pool.unlock();

			if (!isAdd)
			{
				process->processConfig.PID = (maxPID++);
				pool.insert(maxPID, process);
			}
			

			return true;
		}

		unsigned long long getMaxPID()
		{
			return maxPID;
		}

		bool deleteProcess(ProcessScheduleAPI *process)
		{
			if (process == nullptr)
			{
				return false;
			}

			if (process->processConfig.PID == 0)
			{
				return false;
			}

			deleteThread(process);

			auto it = pool.find(process->processConfig.PID);

			pool.lock();
			if (it == pool.end())
			{
				pool.unlock();
				return false;
			}

			it->second = nullptr;
			pool.unlock();

			return true;
		}
	};
}
#endif