#ifndef FLSYSTEM_KERNEL_H
#define FLSYSTEM_KERNEL_H

#include "API/KernelAPI/KernelAPI.h"
#include "API/GC_API/GC_API.h"
#include "ProcessManagement/ProcessSchedule/ProcessSchedule.h"
#include "IPC/IPC.h"

#include <stdarg.h>

namespace FLSYSTEM
{
    class Kernel : public KernelAPI<Kernel>, public GC_API
    {
    private:
        void loadKernel();
        void unloadKernel();

        class KernelRun : public ProcessScheduleAPI
        {
        private:
            Kernel* _kernel_ = nullptr;
            FLSYSTEM_TRANSPLANTATION_TYPE::ThreadDelayConfig config;

        public:
            explicit KernelRun(Kernel* kernel)
            {
                _kernel_ = kernel;
                this->setRunTimeDelay(1);
                this->getLock().lockRead();
                config.time = this->getConfig()->runTimeDelay;
                config.threadConfig = this->getConfig();
				this->getLock().unlockRead();
            }

            virtual ~KernelRun() {}

            FLInline virtual void begin() override { _kernel_->init(); }
            FLInline virtual void loop() override { _kernel_->run(); FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(&config); }
        };

        KernelRun* kernelRun = nullptr;

    public:
        explicit Kernel();
        virtual ~Kernel();

        enum class SysCallNumber
        {
            EmptyRequest = 0x0,
            ThreadCreateRequest,
            ProcessCreateRequest,
			ThreadDeleteRequest,
			ProcessDeleteRequest,
		};

        enum class SysCallError
        {
            NoError = 0x0,
            EmptyPointer,
            UnknownError
        };

        SysCallError sysCall(SysCallNumber number, void* data = nullptr);

		virtual void init();
		virtual void run();
        virtual bool load();

        FLInline void start()
        {
			KernelRun* kr = new KernelRun(this);
			kr->setStackDepth(4096);
			kr->setName("KernelRun");
			kr->setRunTimeDelay(1);
			kr->setPriority(16);
			this->sysCall(SysCallNumber::ProcessCreateRequest, (void*)kr);
        }

        FLInline static void boot()
        {
            Kernel::instance()->load();
        }

		FLInline static void close()
		{
            Kernel::instance()->unload();
		}

		void* operator new(size_t size)
		{
			MemoryManagement::instance();
			IPC::instance();
			ProcessSchedule::instance();
			return MemoryManagement::newData(size);
		}
    };
}



#endif