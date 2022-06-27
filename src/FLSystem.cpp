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
	threadConfig.runTimeDelay = 5;
	threadConfig.stackDepth = 4096;
}

FLSYSTEM::FLSystem::~FLSystem()
{
	mergeList.clear();
}

void FLSYSTEM::FLSystem::merge(FLSYSTEM::ProcessScheduleAPI* api)
{
	mergeList.push_back(api);
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
	kernel.init();
	mergeList.lock();
	for (auto&& i = mergeList.begin(); i != mergeList.end(); i++)
	{
		(*i)->begin();
	}
	mergeList.unlock();
}

void FLSYSTEM::FLSystem::loop()
{
	kernel.run();
	mergeList.lock();
	for (auto&& i = mergeList.begin(); i != mergeList.end(); i++)
	{
		(*i)->loop();
	}
	mergeList.unlock();
}

void FLSYSTEM::FLSystem::start()
{
	if (!isRun)
	{
		isRun = true;
		kernel.processSchedule.createThread(this);
	}

#ifdef FLSYSTEM_TASK_START_SCHEDULER
	vTaskStartScheduler();
#endif

#if ((!defined(FLSYSTEM_ENABLE_MAIN_THREAD)) && (!(defined(FLSYSTEM_TASK_START_SCHEDULER))))
	while (true)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(UINT64_MAX);
	}
#endif
}