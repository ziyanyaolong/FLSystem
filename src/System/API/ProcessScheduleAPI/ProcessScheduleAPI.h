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
		friend class FLSystem;

		struct ProcessConfig
		{
			bool isBegin = false;
			bool isInit = false;
			uint64_t PID = 0;
		};

	protected:
		ProcessScheduleAPI(FLObject* object = nullptr, const std::string& name = std::string("")) : ThreadAPI(object, name) {}
		ProcessScheduleAPI(const std::string &name) : ThreadAPI(name) {}
		ProcessConfig processConfig;

		virtual void begin() = 0;
		virtual void loop() {}

		virtual void run() override
		{
			if (!processConfig.isBegin)
			{
				processConfig.isBegin = true;
				begin();
			}

			while (!this->isExit())
			{
				loop();
				process();
				FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(threadConfig.runTimeDelay);
			}
		}

	public:
		bool isBegin() { return processConfig.isBegin; }
		bool isInit() { return processConfig.isInit; }
		unsigned long long getPID() const { return processConfig.PID; }
		virtual ~ProcessScheduleAPI();
	};
}

#endif