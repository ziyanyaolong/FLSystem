#ifndef FLSYSTEM_THREADAPI_H
#define FLSYSTEM_THREADAPI_H

#include "../EventAPI/EventAPI.h"
#include "../../Kernel/IPC/IPC.h"

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

		struct TaskConfig
		{
			uint32_t runTimeDelay = 1;
			FLTaskPriorityType priority = 3;
			FLTaskStackDepthType stack = 1024;
			FLTaskCoreID core = 0;
			FLTaskReturnedType xReturned = 0;
			FLTaskHandleType* pvCreatedTask = nullptr;
			FLUserDataType userData = nullptr;
		};

	protected:
		TaskConfig taskConfig;
		virtual void run() = 0;
		virtual void exit_out() {}
		virtual void process() override
		{
			FLEventCore.process(static_cast<EventAPI*>(this));
		}

	public:
		explicit ThreadAPI(FLObject* object = nullptr, const std::string &name = std::string("")) : EventAPI(object, name) { isThread = true; }
		ThreadAPI(const std::string &name) : EventAPI(name) { isThread = true; }
		virtual ~ThreadAPI() {}

		TaskConfig& getTaskConfig() { return taskConfig; }
	};
}

#endif