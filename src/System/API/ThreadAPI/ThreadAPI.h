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

	protected:
		FLSYSTEM_TRANSPLANTATION_TYPE::TaskConfig taskConfig;
		virtual void run() = 0;
		virtual void exit_out() {}
		virtual void process() override
		{
			EventCore::process(static_cast<EventAPI*>(this));
		}

	public:
		explicit ThreadAPI(FLObject* object = nullptr, const std::string& name = std::string("")) : EventAPI(object, name) { isThread = true; }
		ThreadAPI(const std::string &name) : EventAPI(name) { isThread = true; }
		virtual ~ThreadAPI() {}

		FLSYSTEM_TRANSPLANTATION_TYPE::TaskConfig& getTaskConfig() { return taskConfig; }
		FLSYSTEM_TRANSPLANTATION_TYPE::TaskConfig* getTaskConfigPointer() { return &taskConfig; }
	};
}

#endif