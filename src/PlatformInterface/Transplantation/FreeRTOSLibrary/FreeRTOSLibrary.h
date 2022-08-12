#ifndef FLSYSTEM_FREERTOSLIBRARY_H
#define FLSYSTEM_FREERTOSLIBRARY_H

#include "../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

#include "FLFRMutex/FLFRMutex.h"
#include "FLFRSemaphore/FLFRSemaphore.h"
#include "FLFRAtomic/FLFRAtomic.h"

#include "../StandardAPI/StandardAPI.h"

#define FLSYSTEM_3RD_STDIO

#ifdef FLSYSTEM_ENABLE_LVGL_MEMORY_MANAGEMENT
#define FLSYSTEM_3RD_LVGL
#endif

#include "../../3rdInclude.h"

#include "FLFRQueue/FLFRQueue.h"

#define FLSYSTEM_FLVECTOR_TYPE FLSYSTEM_FLVECTOR_TYPE_DEFINE
#define FLSYSTEM_FLLIST_TYPE FLSYSTEM_FLLIST_TYPE_DEFINE
#define FLSYSTEM_FLQUEUE_TYPE FLSYSTEM::FLFRQueue
#define FLSYSTEM_FLMAP_TYPE FLSYSTEM_FLMAP_TYPE_DEFINE

namespace FLSYSTEM
{
	class FreeRTOSLibrary : public StandardAPI<FreeRTOSLibrary>
	{
	public:
		explicit FreeRTOSLibrary() : StandardAPI<FreeRTOSLibrary>() {}
		virtual ~FreeRTOSLibrary() {}

		struct DefaultConfig
		{
			static const TickType_t maxDelay = portMAX_DELAY;
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
			TickType_t runTimeDelay = 50;
			void* threadClass = nullptr;
			void* userData = nullptr;
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
			if (pointer == nullptr)
			{
				vTaskDelete(nullptr);
			}

			auto pConfig = static_cast<ThreadConfig*>(pointer);

			if (pConfig == nullptr || pConfig->threadCode == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return;
			}

			vTaskDelete(*(pConfig->createdThread));
		}

		void fl_threadDelay(void* time)
		{
			auto pConfig = static_cast<ThreadDelayConfig*>(time);

			if (pConfig == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return;
			}

			vTaskDelay((TickType_t)pConfig->time);
		}

		void fl_debug(const char* str, void* data = nullptr)
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
			return static_cast<SemaphoreInterface*>(new FLFRSemaphore(type, (UBaseType_t)maxCount, (UBaseType_t)initialCount));
		}
	};
}

#endif

#endif
