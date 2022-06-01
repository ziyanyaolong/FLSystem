#ifndef FLSYSTEM_FREERTOSLIBRARY_H
#define FLSYSTEM_FREERTOSLIBRARY_H

#include "../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

#include "FLFRMutex/FLFRMutex.h"
#include "FLFRSemaphore/FLFRSemaphore.h"
#include "FLFRAtomic/FLFRAtomic.h"

#include "../StandardAPI/StandardAPI.h"

#define FLSYSTEM_3RD_STDIO

#include "../../3rdInclude.h"

namespace FLSYSTEM
{
	class FreeRTOSLibrary : public StandardAPI<FreeRTOSLibrary>
	{
	public:
		explicit FreeRTOSLibrary() : StandardAPI<FreeRTOSLibrary>() {}
		virtual ~FreeRTOSLibrary() {}

		struct DefaultConfig
		{
			const TickType_t maxDelay = portMAX_DELAY;
		};

		struct ThreadConfig
		{
			TaskFunction_t threadCode = nullptr;
			const char* const name = "";
			unsigned short stackDepth = 1024;
			void* parameters = nullptr;
			UBaseType_t priority = 1;
			TaskHandle_t* createdThread = nullptr;
			short coreID = 0;
			BaseType_t returned = 0;
			unsigned long long runTimeDelay = 5;
			void* threadClass = nullptr;
		};

		long fl_createThread(void* data)
		{
			auto pConfig = static_cast<ThreadConfig*>(data);

			if (pConfig == nullptr || pConfig->threadCode == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return 1;
			}

#ifdef FLSYSTEM_ENABLE_FINE_DISTRIBUTION
			pConfig->returned = xTaskCreatePinnedToCore(pConfig->threadCode,
				pConfig->name,
				pConfig->stackDepth,
				data,
				pConfig->priority,
				pConfig->createdThread,
				pConfig->coreID);
#else
			pConfig->returned = xTaskCreate(pConfig->threadCode,
				pConfig->name,
				pConfig->stackDepth,
				data,
				pConfig->priority,
				pConfig->createdThread);
#endif
			return pConfig->returned;
		}

		void fl_exitThread(void* pointer)
		{
			vTaskDelete(pointer);
		}

		void fl_threadDelay(unsigned long long time)
		{
			vTaskDelay((TickType_t)time);
		}

		void fl_debugPrint(const char* str, void* data = nullptr)
		{
			printf("Line:%d, FileName:%s, Debug:%s\n", __LINE__, __FILE__, str);
		}

		template <typename _Ty>
		inline AtomicInterface<_Ty>* fl_createAtomic(FLLockType type)
		{
			return static_cast< AtomicInterface<_Ty>* >(new FLFRAtomic<_Ty>(type));
		}

		inline MutexInterface* fl_createMutex(FLLockType type)
		{
			return static_cast<MutexInterface*>(new FLFRMutex(type));
		}

		inline SemaphoreInterface* fl_createSemaphore(FLLockType type, unsigned long long maxCount = 1, unsigned long long initialCount = 0)
		{
			return static_cast<SemaphoreInterface*>(new FLFRSemaphore(type, maxCount, initialCount));
		}

	};
}

#endif

#endif
