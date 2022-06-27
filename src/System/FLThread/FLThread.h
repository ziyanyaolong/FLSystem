#ifndef FLSYSTEM_FLTHREAD_H
#define FLSYSTEM_FLTHREAD_H

#include "../../FLSystemConfig.h"
#include "../Kernel/API/ThreadAPI/ThreadAPI.h"
#include "../Kernel/kernel.h"

namespace FLSYSTEM
{
    class FLThread : public ThreadAPI
    {
    public:

    private:
        bool isStart = false;
        //SemaphoreHandle_t mutex = nullptr;
        virtual void exit_out();

    public:
        explicit FLThread(FLObject* parent = nullptr);
        virtual ~FLThread();
        virtual void run() { exec(); }
        bool wait(int64_t time = -1);
        void quit();
        void start();

    protected:
    };
}

#endif