#ifndef FLSYSTEM_PROCESSSCHEDULEAPI_H
#define FLSYSTEM_PROCESSSCHEDULEAPI_H

#include "../ThreadAPI/ThreadAPI.h"

namespace FLSYSTEM
{
	class ProcessScheduleAPI : public ThreadAPI
	{
	public:
		friend class ProcessSchedule;
		friend class ProcessPool;

		struct ProcessConfig
		{
			bool isBegin = false;
			bool isInit = false;
			uint64_t PID = 0;
		};

	protected:
		ProcessScheduleAPI(FLObject *object = nullptr, const std::string &name = std::string("")) : ThreadAPI(object, name) {}
		ProcessScheduleAPI(const std::string &name) : ThreadAPI(name) {}
		ProcessConfig processConfig;

		virtual void run() override
		{
			if (!processConfig.isBegin)
			{
				processConfig.isBegin = true;
				begin();
			}

			for (;;)
			{
				loop();
				process();
				FLTaskDelay(taskConfig.runTimeDelay);
			}
			FLExitTask(nullptr);
		}

		virtual void begin() = 0;
		virtual void loop() {}

	public:
		bool isBegin() { return processConfig.isBegin; }
		bool isInit() { return processConfig.isInit; }
		unsigned long long getPID() const { return processConfig.PID; }
		virtual ~ProcessScheduleAPI();
	};
}

#endif