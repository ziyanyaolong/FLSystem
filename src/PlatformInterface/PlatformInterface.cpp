#include "PlatformInterface.h"

FLSYSTEM::FLTaskReturnedType FLSYSTEM::FLNewThread(
	FLSYSTEM::FLTaskFunctionType pxTaskCode,
	FLSYSTEM::FLTaskNameType pcName,
	FLSYSTEM::FLTaskStackDepthType usStackDepth,
	FLSYSTEM::FLTaskParametersType pvParameters,
	FLSYSTEM::FLTaskPriorityType uxPriority,
	FLSYSTEM::FLTaskHandleType* pxCreatedTask,
	FLSYSTEM::FLTaskCoreID xCoreID)
{
#if (FLSYSTEM_ENABLE_THREADLIB == 0)
	std::thread* mthread = new std::thread(pxTaskCode, pvParameters);
	mthread->detach();
	pxCreatedTask = reinterpret_cast<FLSYSTEM::FLTaskHandleType* const>(&mthread);
	if (mthread == nullptr)
	{
		return 0;
	}

	return 1;
#elif (FLSYSTEM_ENABLE_THREADLIB == 1)
#ifndef FLSYSTEM_ENABLE_FINE_DISTRIBUTION
	return xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
#else
	return xTaskCreatePinnedToCore(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, xCoreID);
#endif
#endif
}

void FLSYSTEM::FLTaskDelay(long long time)
{
#if (FLSYSTEM_ENABLE_THREADLIB == 0)
	if (time < 0)
	{
		std::this_thread::yield();
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
#elif (FLSYSTEM_ENABLE_THREADLIB == 1)
	if (time < 0)
	{
		vTaskDelay(portMAX_DELAY);
	}
	else
	{
		vTaskDelay(time);
	}
#endif
}


void FLSYSTEM::FLExitTask(FLSYSTEM::FLTaskHandleType data)
{
#if (FLSYSTEM_ENABLE_THREADLIB == 0)
	FLTaskDelay(-1);
#elif (FLSYSTEM_ENABLE_THREADLIB == 1)
	vTaskDelete(data);
#endif
}

void FLSYSTEM::FLException(const char* data)
{
#if (FLSYSTEM_EXCEPTION_MODE == 0)
	throw data;

#elif (FLSYSTEM_EXCEPTION_MODE == 1)
	abort();

#elif (FLSYSTEM_EXCEPTION_MODE == 2)

#ifdef FLSYSTEM_ESPRESSIF_BOARD
	abort();

#elif defined FLSYSTEM_ARDUINO_BOARD

#elif defined FLSYSTEM_STM32_BOARD

#elif defined FLSYSTEM_UNKNOW_BOARD
	throw data;

#endif

#else
#endif
}