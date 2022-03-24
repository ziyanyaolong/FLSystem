#ifndef FLSYSTEM_FLSYSTEM_MAIN_H
#define FLSYSTEM_FLSYSTEM_MAIN_H

#include "FLSystemConfig.h"
#include "Driver/ExternalStorage/ExternalStorage.h"
#include "System/BaseDataTable/BaseDataTable.h"
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

	protected:
		virtual void loop() override;
		virtual void begin() override;
		virtual bool event(FLEvent* event) override;

	public:
		virtual ~FLSystem();
		FLSystem();

		void start();
		void registerProcess(ProcessScheduleAPI* api);
		void (*initInOther)(FLSystem* flSystem) = nullptr;
		void (*runInOther)(FLSystem* flSystem) = nullptr;

	};
}

#endif