#include "FLSystem.h"

namespace FLSYSTEM
{
	FLSystem* FL_BIOS = new FLSystem();
}

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

FLSYSTEM::FLSystem::FLSystem()
{
	//Kernel::boot();
	//this->setRunTimeDelay(5);
	//this->setStackDepth(4096);
}

FLSYSTEM::FLSystem::~FLSystem()
{
	//Kernel::close();
	//mergeList.clear();
}

//bool FLSYSTEM::FLSystem::event(FLEvent* event)
//{
//	if (event->type() == FLEvent::Type::RegiserEvent)
//	{
//		auto process = static_cast<ProcessScheduleAPI*>(event->getUserData());
//		if (process == nullptr)
//		{
//			return false;
//		}
//		kernel.processSchedule.createProcess(process);
//		return true;
//	}
//	return false;
//}

void FLSYSTEM::FLSystem::registerProcess(ProcessScheduleAPI* api)
{
	Kernel::instance()->sysCall(Kernel::SysCallNumber::ProcessCreateRequest, api);
}

void FLSYSTEM::FLSystem::registerThread(ThreadAPI* api)
{
	Kernel::instance()->sysCall(Kernel::SysCallNumber::ThreadCreateRequest, api);
}
//void FLSYSTEM::FLSystem::begin()
//{
//	kernel.loadKernel();
//	kernel.init();
//	mergeList.lock();
//	for (auto&& i = mergeList.begin(); i != mergeList.end(); i++)
//	{
//		(*i)->begin();
//	}
//	mergeList.unlock();
//}
//
//void FLSYSTEM::FLSystem::loop()
//{
//	kernel.run();
//	mergeList.lock();
//	for (auto&& i = mergeList.begin(); i != mergeList.end(); i++)
//	{
//		(*i)->loop();
//	}
//	mergeList.unlock();
//}

void FLSYSTEM::FLSystem::init()
{
}

void FLSYSTEM::FLSystem::start()
{
	if (!isRun)
	{
		isRun = true;
		Kernel::instance()->start();
	}

#ifdef FLSYSTEM_TASK_START_SCHEDULER
	vTaskStartScheduler();
#endif

#if ((!defined(FLSYSTEM_ENABLE_MAIN_THREAD)) && (!(defined(FLSYSTEM_TASK_START_SCHEDULER))))
	FLSYSTEM_TRANSPLANTATION_TYPE::ThreadDelayConfig config;
	config.threadConfig = nullptr;
	//config.time = FLSYSTEM_TRANSPLANTATION_TYPE::DefaultConfig::maxDelay;
	config.time = 5;
	while (true)
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(&config);
	}
#endif
}