#ifndef FLSYSTEM_$capitalsafeitemname$_H
#define FLSYSTEM_$capitalsafeitemname$_H

#include "../../TransplantationInterface/TransplantationInterface.h"

#ifdef FLSYSTEM_3RD_FREERTOS

namespace FLSYSTEM
{
	class FreeRTOSLibrary : public TransplantationInterface
	{
	public:
		explicit FreeRTOSLibrary() {}
		virtual ~FreeRTOSLibrary() {}

		struct TaskConfig
		{
			TaskFunction_t taskCode = nullptr;
			const char* const name = "";
			unsigned short stackDepth = 1024;
			void* parameters = nullptr;
			UBaseType_t priority = 1;
			TaskHandle_t* createdTask = nullptr;
			short coreID = 0;
			BaseType_t returned = 0;
			unsigned long long runTimeDelay = 1;
			void* threadClass = nullptr;
		};

		virtual long createTask(void* data) override
		{
			auto pConfig = static_cast<TaskConfig*>(data);

			if (pConfig == nullptr || pConfig->taskCode == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return 1;
			}

#ifdef FLSYSTEM_ENABLE_FINE_DISTRIBUTION
			pConfig->returned = xTaskCreatePinnedToCore(pConfig->taskCode,
				pConfig->name,
				pConfig->stackDepth,
				data,
				pConfig->priority,
				pConfig->createdTask
				pConfig->coreID);
#else
			pConfig->returned = xTaskCreate(pConfig->taskCode,
				pConfig->name,
				pConfig->stackDepth,
				data,
				pConfig->priority,
				pConfig->createdTask);
#endif
			return pConfig->returned;
		}

		virtual void exitTask(void* pointer) override
		{
			vTaskDelete(pointer);
		}

		virtual void taskDelay(long long time) override
		{
			if (time < 0)
			{
				vTaskDelay(portMAX_DELAY);
			}
			else
			{
				vTaskDelay(time);
			}
		}

		virtual void exception(const char* data) override
		{
			defaultException(data);
		}
	};
}

#endif

#endif
