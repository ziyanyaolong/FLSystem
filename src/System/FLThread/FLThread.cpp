#include "FLThread.h"

FLSYSTEM::FLThread::FLThread(FLObject* parent) : ThreadAPI(parent)
{
    //mutex = ::xSemaphoreCreateMutex();

    //if (mutex == nullptr)
    //{
    //    throw std::string("ERROR:Unable to create mutex. - " + this->readName());
    //}
}

FLSYSTEM::FLThread::~FLThread()
{
    //::vSemaphoreDelete(mutex);
}

bool FLSYSTEM::FLThread::wait(int64_t time)
{
    //return ::xSemaphoreTake(mutex, time);
    return true;
}

void FLSYSTEM::FLThread::quit()
{
    exit();
    // this->postEvent(this, new FLEvent(FLEvent::Type::ExitLoop));
}

void FLSYSTEM::FLThread::exit_out()
{
    //::xSemaphoreGive(mutex);
}

void FLSYSTEM::FLThread::start()
{
    if(isStart)
        return;

    isStart = true;
    Kernel::processSchedule.createThread(this);
}
