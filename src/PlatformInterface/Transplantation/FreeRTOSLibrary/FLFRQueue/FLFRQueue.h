#ifndef FLSYSTEM_FLFRQUEUE_H
#define FLSYSTEM_FLFRQUEUE_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

#define FLSYSTEM_3RD_FREERTOS
#define FLSYSTEM_3RD_CSTDDEF

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	template <typename T>
	class FLFRQueue
	{
	private:
		uint16_t sendTimeOut = 0;
		uint16_t receiveTimeOut = 0;
		QueueHandle_t _queueHandle = nullptr;

	public:
		FLFRQueue(const UBaseType_t number)
		{
			QueueHandle_t queueHandle = xQueueCreate(number, sizeof(T));
			_queueHandle = queueHandle;
		}
		FLFRQueue() : FLFRQueue(16) {}

		virtual ~FLFRQueue()
		{
			this->clear();
			vQueueDelete(_queueHandle);
		}

		bool push(const T& data)
		{

			if (uxQueueSpacesAvailable(_queueHandle) == 0)
			{
				return false;
			}

			xQueueSend(_queueHandle, &data, sendTimeOut);
			return true;
		}

		std::size_t size()
		{
			auto tempData = uxQueueMessagesWaiting(_queueHandle);
			return tempData;
		}

		void clear()
		{
			xQueueReset(_queueHandle);
		}

		bool empty()
		{
			auto tempData = this->size();
			if (tempData == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		T front()
		{
			T tempData = T();
			xQueuePeek(_queueHandle, &tempData, receiveTimeOut);
			return tempData;
		}

		T read()
		{
			T tempData = T();
			xQueueReceive(_queueHandle, &tempData, receiveTimeOut);
			return tempData;
		}

		void pop()
		{
			T tempData = T();
			xQueueReceive(_queueHandle, &tempData, receiveTimeOut);
		}
	};
}

#endif

#endif
