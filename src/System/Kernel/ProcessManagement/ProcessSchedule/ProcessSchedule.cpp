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
        FLException("ERROR In CreateThread:fun pointer or config pointer is empty!");
        return -1;
    }
    createThreadLock.lock();

    thread->taskConfig.xReturned = FLNewThread(
        &FLSYSTEM::ProcessSchedule::_runMiddle_T,
        (std::string("FLSYSTEM.Thread.") + thread->readName()).c_str(),
        thread->taskConfig.stack,
        thread,
        thread->taskConfig.priority,
        thread->taskConfig.pvCreatedTask,
        thread->taskConfig.core);

    processPool.addThread(thread);

    createThreadLock.unlock();

    return thread->taskConfig.xReturned;
}

int FLSYSTEM::ProcessSchedule::createProcess(ProcessScheduleAPI *process)
{
    if (process == nullptr)
    {
        FLException("ERROR In CreateThread:fun pointer or config pointer is empty!");
        return -1;
    }

    createThreadLock.lock();

    process->taskConfig.xReturned = FLNewThread(
        &FLSYSTEM::ProcessSchedule::_runMiddle_P,
        (std::string("FLSYSTEM.Process.") + process->readName()).c_str(),
        process->taskConfig.stack,
        process,
        process->taskConfig.priority,
        process->taskConfig.pvCreatedTask,
        process->taskConfig.core);

    processPool.addProcess(process);

    createThreadLock.unlock();

    return process->taskConfig.xReturned;
}

void FLSYSTEM::ProcessSchedule::_runMiddle_P(void *process)
{
    auto _process_ = static_cast<ProcessScheduleAPI *>(process);

    if (_process_ == nullptr)
    {
        FLException("ERROR:process pointer is empty!");
        return;
    }

    _process_->run();
    _process_->exit_out();
    FLSYSTEM::ProcessSchedule::processPool.deleteProcess(_process_);
    FLExitTask(nullptr);
}
void FLSYSTEM::ProcessSchedule::_runMiddle_T(void *thread)
{
    auto _thread_ = static_cast<ThreadAPI *>(thread);

    if (_thread_ == nullptr)
    {
        FLException("ERROR:thread pointer is empty!");
        return;
    }

    _thread_->run();
    _thread_->exit_out();
    FLSYSTEM::ProcessSchedule::processPool.deleteThread(_thread_);
    FLExitTask(nullptr);
}

void FLSYSTEM::ProcessSchedule::run()
{
}
