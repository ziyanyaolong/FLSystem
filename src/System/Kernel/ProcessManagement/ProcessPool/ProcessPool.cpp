#include "ProcessPool.h"

FLSYSTEM::ProcessPool::ProcessPool() : GC_API()
{
	pool = new FLMap<uint64_t, ProcessScheduleAPI*>(FLMap<uint64_t, ProcessScheduleAPI*>::Mode::NoLock);
	threadPool = new FLVector<ThreadAPI*>(FLVector<ThreadAPI*>::Mode::NoLock);
}

FLSYSTEM::ProcessPool::~ProcessPool()
{
	pool->deleteLater();
	threadPool->deleteLater();
}

bool FLSYSTEM::ProcessPool::addThread(ThreadAPI* thread)
{
	if (thread == nullptr)
	{
		return false;
	}

	if (std::find(threadPool->begin(), threadPool->end(), thread) != threadPool->end())
	{
		return false;
	}

	threadPool->push_back(thread);
	return true;
}

bool FLSYSTEM::ProcessPool::deleteThread(ThreadAPI* thread)
{
	if (thread == nullptr)
	{
		return false;
	}

	auto it = std::find(threadPool->begin(), threadPool->end(), thread);
	if (it == threadPool->end())
	{
		return false;
	}

	threadPool->erase(it);
	return true;
}

bool FLSYSTEM::ProcessPool::addProcess(ProcessScheduleAPI* process)
{
	if (process == nullptr)
	{
		return false;
	}

	if (process->processConfig.PID != 0 || !(this->addThread(process)))
	{
		return false;
	}

	bool isAdd = false;

	for (auto i = pool->begin(); i != pool->end(); i++)
	{
		if (i->second == nullptr)
		{
			process->processConfig.PID = i->first;
			i->second = process;
			isAdd = true;
		}
	}

	if (!isAdd)
	{
		process->processConfig.PID = (maxPID++);
		pool->insert(maxPID, process);
	}


	return true;
}

bool FLSYSTEM::ProcessPool::deleteProcess(ProcessScheduleAPI* process)
{
	if (process == nullptr)
	{
		return false;
	}

	if (process->processConfig.PID == 0)
	{
		return false;
	}

	this->deleteThread(process);

	auto it = pool->find(process->processConfig.PID);

	if (it == pool->end())
	{
		return false;
	}

	it->second = nullptr;

	return true;
}