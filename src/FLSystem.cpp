#include "FLSystem.h"

#ifdef FLSYSTEM_ENABLE_LVGL_8
// void FLSystem::readEvent(lv_event_t *e)
// {
//     if (FLSystem::appList.find(e->target) != FLSystem::appList.end())
//     {
//         FLSystem::appList[e->target]->run(e->target, e->code);
//         FLSystem::appList[e->target]->setAddLoop(true);
//     }
// }
#endif

FLSYSTEM::FLSystem::FLSystem() : ProcessScheduleAPI()
{
	taskConfig.runTimeDelay = 5;
	taskConfig.stackDepth = 4096;
}

FLSYSTEM::FLSystem::~FLSystem()
{
}

bool FLSYSTEM::FLSystem::event(FLEvent* event)
{
	if (event->type() == FLEvent::Type::RegiserEvent)
	{
		auto process = static_cast<ProcessScheduleAPI*>(event->getUserData());
		if (process == nullptr)
		{
			return false;
		}
		kernel.processSchedule.createProcess(process);
		return true;
	}
	return false;
}

void FLSYSTEM::FLSystem::registerProcess(ProcessScheduleAPI* api)
{
	FLEvent* event = new FLEvent(FLEvent::RegiserEvent);
	event->setUserData(static_cast<void*>(api));
	FLEventCore.postEvent(this, event);
}

void FLSYSTEM::FLSystem::begin()
{
#ifdef FLSYSTEM_3RD_LVGL
	lv_init();
#endif
	kernel.init();

	if (initInOther != nullptr)
	{
		initInOther(this);
	}
}

void FLSYSTEM::FLSystem::loop()
{
	if (runInOther != nullptr)
	{
		runInOther(this);
	}

#ifdef FLSYSTEM_3RD_LVGL
	lv_task_handler();

#ifdef FLSYSTEM_ENABLE_LVGL_TICK_SYNCH
	lv_tick_inc(taskConfig.runTimeDelay);

#endif

#endif
	kernel.run();

}

void FLSYSTEM::FLSystem::start()
{
	if (!isRun)
	{
		isRun = true;
		kernel.processSchedule.createThread(this);
	}

#if (FLSYSTEM_ENABLE_THREADLIB == 0)

#ifndef FLSYSTEM_ENABLE_MAIN_THREAD
	FLSYSTEM_TRANSPLANTATION_INSTANCE->taskDelay(0);

#endif
	
#elif (FLSYSTEM_ENABLE_THREADLIB == 1)

#ifdef FLSYSTEM_TASK_START_SCHEDULER
	vTaskStartScheduler();

#else

#ifndef FLSYSTEM_ENABLE_MAIN_THREAD
	FLSYSTEM_TRANSPLANTATION_INSTANCE->exitTask(nullptr);

#endif

#endif
	
#endif

}