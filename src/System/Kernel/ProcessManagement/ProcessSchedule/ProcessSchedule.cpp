#include "ProcessSchedule.h"

FLSYSTEM::ProcessSchedule::ProcessSchedule() : KernelAPI(), GC_API()
{
}

FLSYSTEM::ProcessSchedule::~ProcessSchedule()
{
	if (createThreadLock)
	{
		delete createThreadLock;
		createThreadLock = nullptr;
	}

	if (processPool)
	{
		delete processPool;
		processPool = nullptr;
	}
}

void FLSYSTEM::ProcessSchedule::init()
{
}

bool FLSYSTEM::ProcessSchedule::load()
{
	if (createThreadLock == nullptr)
	{
		createThreadLock = new FLLock();
	}

	if (processPool == nullptr)
	{
		processPool = new ProcessPool();
	}
	return true;
}

int FLSYSTEM::ProcessSchedule::createThread(ThreadAPI* thread)
{
	if (thread == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR In CreateThread:fun pointer or config pointer is empty!");
		return -1;
	}
	createThreadLock->lock();

	thread->_lock.lockWrite();
	thread->_threadConfig_.threadCode = &FLSYSTEM::ProcessSchedule::_runMiddle_T;
	thread->_threadConfig_.threadClass = (void*)thread;
	thread->_lock.unlockWrite();

	auto tempReturned = FLSYSTEM_TRANSPLANTATION_INSTANCE->createThread(static_cast<void*>(&(thread->_threadConfig_)));

	thread->_lock.lockWrite();
	thread->_threadConfig_.returned = tempReturned;
	thread->_lock.unlockWrite();

	processPool->addThread(thread);

	createThreadLock->unlock();

	return tempReturned;
}

int FLSYSTEM::ProcessSchedule::createProcess(ProcessScheduleAPI* process)
{
	if (process == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR In CreateThread:fun pointer or config pointer is empty!");
		return -1;
	}

	createThreadLock->lock();

	process->_lock.lockWrite();

	process->_threadConfig_.threadCode = &FLSYSTEM::ProcessSchedule::_runMiddle_P;
	process->_threadConfig_.threadClass = (void*)process;
	process->_lock.unlockWrite();

	auto tempReturn = FLSYSTEM_TRANSPLANTATION_INSTANCE->createThread(&(process->_threadConfig_));

	process->_lock.lockWrite();
	process->_threadConfig_.returned = tempReturn;
	process->_lock.unlockWrite();

	processPool->addProcess(process);

	createThreadLock->unlock();

	return tempReturn;
}

void FLSYSTEM::ProcessSchedule::deleteProcess(ProcessScheduleAPI* process)
{
	process->deleteLater();
}

void FLSYSTEM::ProcessSchedule::deleteThread(ThreadAPI* thread)
{
	thread->deleteLater();
}

void FLSYSTEM::ProcessSchedule::_runMiddle_P(void* threadConfig)
{
	auto threadConfigPoiner = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig*>(threadConfig);

	if (threadConfigPoiner == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:process config pointer is empty!");
		return;
	}

	auto processPointer = static_cast<ProcessScheduleAPI*>(threadConfigPoiner->threadClass);

	if (processPointer == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:process pointer is empty!");
		return;
	}
	processPointer->run();
	processPointer->exit();
	processPointer->exitOut();
	FLSYSTEM::ProcessSchedule::instance()->processPool->deleteProcess(processPointer);
	FLSYSTEM_TRANSPLANTATION_INSTANCE->exitThread(threadConfigPoiner);
	processPointer->deleteLater();


}
void FLSYSTEM::ProcessSchedule::_runMiddle_T(void* threadConfig)
{
	auto threadConfigPoiner = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig*>(threadConfig);

	if (threadConfigPoiner == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:thread config pointer is empty!");
		return;
	}

	auto threadPointer = static_cast<ThreadAPI*>(threadConfigPoiner->threadClass);

	if (threadPointer == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:thread pointer is empty!");
		return;
	}
	threadPointer->run();
	threadPointer->exit();
	threadPointer->exitOut();
	FLSYSTEM::ProcessSchedule::instance()->processPool->deleteThread(threadPointer);
	FLSYSTEM_TRANSPLANTATION_INSTANCE->exitThread(threadConfigPoiner);
	threadPointer->deleteLater();
}

void FLSYSTEM::ProcessSchedule::run()
{
}