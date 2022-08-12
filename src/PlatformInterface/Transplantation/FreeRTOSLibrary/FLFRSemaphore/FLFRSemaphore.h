#ifndef FLSYSTEM_FLFRSEMAPHORE_H
#define FLSYSTEM_FLFRSEMAPHORE_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

#include "../../FLTRInclude.h"

#define FLSYSTEM_3RD_FREERTOS

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	class FLFRSemaphore : public SemaphoreInterface
	{
	private:
		SemaphoreHandle_t _semaphore = nullptr;

	public:
		explicit FLFRSemaphore(FLLockType type = FLLockType::Binary, UBaseType_t uxMaxCount = 1, UBaseType_t uxInitialCount = 0);
		virtual ~FLFRSemaphore();

		virtual bool take(unsigned long long xTicksToWait = portMAX_DELAY);
		virtual void give() override;

		bool giveFromISR(BaseType_t* const pxHigherPriorityTaskWoken = nullptr);
		bool takeFromISR(BaseType_t* const pxHigherPriorityTaskWoken = nullptr);
	};
}

#endif

#endif