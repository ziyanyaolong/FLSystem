#include "ProcessSchedule.h"

FLSYSTEM::ProcessPool FLSYSTEM::ProcessSchedule::processPool;

FLSYSTEM::ProcessSchedule::ProcessSchedule()
{
}

FLSYSTEM::ProcessSchedule::~ProcessSchedule()
{
}

void FLSYSTEM::ProcessSchedule::begin()
{
}

int FLSYSTEM::ProcessSchedule::createThread(ThreadAPI* thread)
{
	if (thread == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR In CreateThread:fun pointer or config pointer is empty!");
		return -1;
	}
	createThreadLock.lock();

	thread->getThreadConfig().threadCode = &FLSYSTEM::ProcessSchedule::_runMiddle_T;
	thread->getThreadConfig().threadClass = (void*)thread;
	thread->threadConfig.returned = FLSYSTEM_TRANSPLANTATION_INSTANCE->createThread(static_cast<void*>(thread->getThreadConfigPointer()));

	processPool.addThread(thread);

	createThreadLock.unlock();

	return thread->threadConfig.returned;
}

int FLSYSTEM::ProcessSchedule::createProcess(ProcessScheduleAPI* process)
{
	if (process == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR In CreateThread:fun pointer or config pointer is empty!");
		return -1;
	}

	createThreadLock.lock();

	process->getThreadConfig().threadCode = &FLSYSTEM::ProcessSchedule::_runMiddle_P;
	process->getThreadConfig().threadClass = (void*)process;
	process->threadConfig.returned = FLSYSTEM_TRANSPLANTATION_INSTANCE->createThread(process->getThreadConfigPointer());

	processPool.addProcess(process);

	createThreadLock.unlock();

	return process->threadConfig.returned;
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
	FLSYSTEM::ProcessSchedule::processPool.deleteProcess(processPointer);
	FLSYSTEM_TRANSPLANTATION_INSTANCE->exitThread(threadConfigPoiner);
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
	FLSYSTEM::ProcessSchedule::processPool.deleteThread(threadPointer);
	FLSYSTEM_TRANSPLANTATION_INSTANCE->exitThread(threadConfigPoiner);
}

void FLSYSTEM::ProcessSchedule::run()
{
}