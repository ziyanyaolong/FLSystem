#ifndef FLSYSTEM_THREADAPI_H
#define FLSYSTEM_THREADAPI_H

#include "../EventAPI/EventAPI.h"
#include "../../Kernel/IPC/IPC.h"
#include "../../Kernel/IPC/Lock/FLLock/FLLock.h"

namespace FLSYSTEM
{
	class ThreadAPI : public EventAPI
	{
	public:
		friend class ProcessSchedule;
		friend class ProcessPool;
		friend class FLThread;

		enum class ThreadState
		{
			Delete,
			Stop,
			Run,
			Ready
		};

	private:
		FLLock _finishProcess;

	protected:
		FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig threadConfig;
		virtual void run() = 0;
		inline virtual void exitOut() { _finishProcess.unlock(); }
		inline virtual void process() override
		{
			EventCore::process(static_cast<EventAPI*>(this));
		}

	public:
		ThreadAPI(const std::string& name) : EventAPI(name) { isThread = true; }
		explicit ThreadAPI(FLObject* object = nullptr, const std::string& name = std::string("")) : ThreadAPI(name) {}
		virtual ~ThreadAPI() {}

		inline virtual int exit() { _finishProcess.lock(); return 0; }
		inline virtual void start() { run(); }

		inline bool isExit() { return _finishProcess.isLocking(); }

		inline void exec()
		{
			while (!_finishProcess.isLocking())
			{
				process();
				FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(threadConfig.runTimeDelay);
			}
		}

		FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig& getThreadConfig() { return threadConfig; }
		FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig* getThreadConfigPointer() { return &threadConfig; }
	};
}

#endif