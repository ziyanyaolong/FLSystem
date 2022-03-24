#ifndef FLSYSTEM_FLFRSEMAPHORE_H
#define FLSYSTEM_FLFRSEMAPHORE_H

#include "../../../../../PlatformInterface/PlatformInterface.h"

#ifdef FLSYSTEM_3RD_FREERTOS

namespace FLSYSTEM
{
	class FLFRSemaphore
	{
	public:
		enum class Type
		{
			Binary,
			Counting,
			Mutex,
			RecursiveMutex
		};

	private:
		SemaphoreHandle_t semaphore = nullptr;
		FLFRSemaphore::Type _type = FLFRSemaphore::Type::Binary;

	public:
		explicit FLFRSemaphore(FLFRSemaphore::Type type = FLFRSemaphore::Type::Mutex, UBaseType_t uxMaxCount = configSUPPORT_DYNAMIC_ALLOCATION, UBaseType_t uxInitialCount = 0);
		virtual ~FLFRSemaphore();

		bool give();
		bool take(TickType_t xTicksToWait = portMAX_DELAY);
		bool giveFromISR(BaseType_t* const pxHigherPriorityTaskWoken = nullptr);
		bool takeFromISR(BaseType_t* const pxHigherPriorityTaskWoken = nullptr);
		bool isRecursiveMutex();
		bool isMutex();
		bool isBinary();
		bool isCounting();
		FLFRSemaphore::Type type() { return _type; }
		UBaseType_t getCount();
	};
}

#endif

#endif