#ifndef FLSYSTEM_FLSYSTEM_MAIN_H
#define FLSYSTEM_FLSYSTEM_MAIN_H

#include "PlatformInterface/PlatformInterface.h"
#include "Driver/ExternalStorage/ExternalStorage.h"
#include "Driver/Display/Display.h"
#include "System/Kernel/Kernel.h"
#include "API_Library.h"

namespace FLSYSTEM
{
	  
	class FLSystem : public ProcessScheduleAPI
	{
	private:
		Kernel kernel;
		bool isRun = false;
		FLQueue<ProcessScheduleAPI*> processList;
		FLVector<ProcessScheduleAPI*> mergeList;

	protected:
		virtual void loop() override;
		virtual void begin() override;
		virtual bool event(FLEvent* event) override;

	public:
		virtual ~FLSystem();
		FLSystem();

		void setTransplantation() {}
		void start();
		void registerProcess(ProcessScheduleAPI* api);
		void merge(ProcessScheduleAPI* api);
	};
}

#endif