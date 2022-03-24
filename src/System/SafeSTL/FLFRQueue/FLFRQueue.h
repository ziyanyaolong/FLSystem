#ifndef FLSYSTEM_FLFRQUEUE_H
#define FLSYSTEM_FLFRQUEUE_H

#include "../../../PlatformInterface/PlatformInterface.h"

#ifdef FLSYSTEM_3RD_FREERTOS

#include "../STL_Bass/STL_Basic.h"

namespace FLSYSTEM
{
	template <typename T>
	class FLFRQueue : public STL_Basic
	{
	private:
		uint16_t sendTimeOut = 0;
		uint16_t receiveTimeOut = 0;
		QueueHandle_t _queueHandle = nullptr;

	public:
		FLFRQueue(std::size_t number) : STL_Basic()
		{
			QueueHandle_t queueHandle = xQueueCreate(number, sizeof(T));
			if (queueHandle == nullptr)
			{
				FLEventSizeType("ERROR:Can't New QueueHandle");
			}
			_queueHandle = queueHandle;
		}
		FLFRQueue() : FLFRQueue(16) {}

		virtual ~FLFRQueue()
		{
			this->clear();
			vQueueDelete(_queueHandle);
		}

		bool push_back(const T& data)
		{
			setWrite();
			if (uxQueueSpacesAvailable(_queueHandle) == 0)
			{
				resetWrite();
				return false;
			}

			xQueueSend(_queueHandle, &data, sendTimeOut);

			resetWrite();
			return true;
		}

		std::size_t size()
		{
			setRead();
			auto tempData = uxQueueMessagesWaiting(_queueHandle);
			resetRead();
			return tempData;
		}

		void clear()
		{
			setWrite();
			xQueueReset(_queueHandle);
			resetWrite();
		}

		bool empty()
		{
			setRead();
			auto tempData = this->size();
			resetRead();
			if (tempData == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		T peek()
		{
			T tempData = T();
			setRead();
			xQueuePeek(_queueHandle, &tempData, receiveTimeOut);
			resetRead();
			return tempData;
		}

		T read()
		{
			T tempData = T();
			this->setWrite();
			xQueueReceive(_queueHandle, &tempData, receiveTimeOut);
			this->resetWrite();
			return tempData;
		}
	};
}

#endif

#endif
