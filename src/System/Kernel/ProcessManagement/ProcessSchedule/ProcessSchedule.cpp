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

int FLSYSTEM::ProcessSchedule::createThread(ThreadAPI *thread)
{
    if (thread == nullptr)
    {
        FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR In CreateThread:fun pointer or config pointer is empty!");
        return -1;
    }
    createThreadLock.lock();

    thread->getTaskConfig().taskCode = &FLSYSTEM::ProcessSchedule::_runMiddle_T;
    thread->getTaskConfig().threadClass = (void*)thread;
    thread->taskConfig.returned = FLSYSTEM_TRANSPLANTATION_INSTANCE->createTask(static_cast<void*>(thread->getTaskConfigPointer()));

    processPool.addThread(thread);

    createThreadLock.unlock();

    return thread->taskConfig.returned;
}

int FLSYSTEM::ProcessSchedule::createProcess(ProcessScheduleAPI *process)
{
    if (process == nullptr)
    {
        FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR In CreateThread:fun pointer or config pointer is empty!");
        return -1;
    }

    createThreadLock.lock();

	process->getTaskConfig().taskCode = &FLSYSTEM::ProcessSchedule::_runMiddle_P;
    process->getTaskConfig().threadClass = (void*)process;
    process->taskConfig.returned = FLSYSTEM_TRANSPLANTATION_INSTANCE->createTask(process->getTaskConfigPointer());

    processPool.addProcess(process);

    createThreadLock.unlock();

    return process->taskConfig.returned;
}

void FLSYSTEM::ProcessSchedule::_runMiddle_P(void * taskConfig)
{
    auto taskConfigPoiner = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::TaskConfig*>(taskConfig);

    if (taskConfigPoiner == nullptr)
    {
        FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:process config pointer is empty!");
        return;
    }

    auto processPointer = static_cast<ProcessScheduleAPI*>(taskConfigPoiner->threadClass);

    if (processPointer == nullptr)
    {
        FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:process pointer is empty!");
        return;
    }
    processPointer->run();
    processPointer->exit_out();
    FLSYSTEM::ProcessSchedule::processPool.deleteProcess(processPointer);
    FLSYSTEM_TRANSPLANTATION_INSTANCE->exitTask(nullptr);
}
void FLSYSTEM::ProcessSchedule::_runMiddle_T(void *taskConfig)
{
	auto taskConfigPoiner = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::TaskConfig*>(taskConfig);

	if (taskConfigPoiner == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:thread config pointer is empty!");
		return;
	}

	auto threadPointer = static_cast<ThreadAPI*>(taskConfigPoiner->threadClass);

	if (threadPointer == nullptr)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("ERROR:thread pointer is empty!");
		return;
	}
    threadPointer->run();
    threadPointer->exit_out();
	FLSYSTEM::ProcessSchedule::processPool.deleteThread(threadPointer);
	FLSYSTEM_TRANSPLANTATION_INSTANCE->exitTask(nullptr);
}

void FLSYSTEM::ProcessSchedule::run()
{
}
