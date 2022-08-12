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

		bool isBegin();
		bool isInit();

		unsigned long long getPID();

		virtual ~ProcessScheduleAPI();

	protected:
		ProcessScheduleAPI(FLObject* object = nullptr, const std::string& name = std::string(""));
		ProcessConfig processConfig;

		virtual void begin() = 0;
		virtual void loop() {}

		FLInline void runInEventLoop() override { loop(); }

		virtual void run() override
		{
			if (!processConfig.isBegin)
			{
				processConfig.isBegin = true;
				begin();
			}

			this->exec();
		}
	};
}

#endif