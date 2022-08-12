#include "EventCore.h"

FLSYSTEM::EventCore::EventCore() : EventAPI()
{
	isThread = true;
}

FLSYSTEM::EventCore::~EventCore()
{
}

void FLSYSTEM::EventCore::process(EventAPI* eventAPI)
{
	auto* eventTable = condense(eventAPI, 16);

	if (eventTable == nullptr)
		return;

	notify(eventTable->object, eventTable->event);
	delete eventTable->event;
	delete eventTable;
	eventTable = nullptr;
}

bool FLSYSTEM::EventCore::sendEvent(FLObject* receiver, FLEvent* event)
{
	return notify(receiver, event);
}

bool FLSYSTEM::EventCore::postEvent(FLObject* receiver, FLEvent* event)
{
	if (receiver == nullptr || event == nullptr)
	{
		return false;
	}
	else if (receiver->isThread)
	{
		EventTable* et = new EventTable();
		et->object = receiver;
		et->event = event;
		if ((static_cast<EventAPI*>(receiver))->eventQueue.push_back(et))
		{
			return true;
		}
		else
		{
			delete event;
			event = nullptr;
			delete et;
			return false;
		}
	}

	auto parent = receiver;
	while (true)
	{
		if (parent == nullptr)
		{
			return false;
		}
		else if (parent->isThread)
		{
			EventTable* et = new EventTable();
			et->object = receiver;
			et->event = event;
			if ((static_cast<EventAPI*>(parent))->eventQueue.push_back(et))
			{
				return true;
			}
			else
			{
				delete event;
				event = nullptr;
				delete et;
				return false;
			}
		}

		parent = parent->getParent();
	}

	return false;
}

bool FLSYSTEM::EventCore::notify(FLObject* object, FLEvent* event)
{
	if (object == nullptr || event == nullptr)
	{
		return false;
	}

	if (object->isInstallEventFilter())
	{
		bool isFilterSuccessfully = false;
		object->eventFilters->lock();
		for (auto i = object->eventFilters->begin(); i != object->eventFilters->end(); i++)
		{
			if ((*i)->eventFilter(object, event))
			{
				if (!isFilterSuccessfully)
					isFilterSuccessfully = true;
			}
		}
		object->eventFilters->unlock();

		if (isFilterSuccessfully)
		{
			return true;
		}
	}

	if (object->event(event))
	{
		return true;
	}

	if (object->getParent() == nullptr)
	{
		return false;
	}

	if (object->isThread)
	{
		return false;
	}

	return notify(object->getParent(), event);
}

FLSYSTEM::EventCore::EventTable* FLSYSTEM::EventCore::condense(EventAPI* eventAPI, std::size_t number)
{
	if (eventAPI->eventQueue.empty())
	{
		return nullptr;
	}

	EventTable* eventTable = nullptr;
	bool isCompare = true;

	//获取第一条事件（参照物）
	while (true)
	{
		eventTable = eventAPI->eventQueue.read();

		if (eventTable == nullptr)
		{
			if (eventAPI->eventQueue.empty())
			{
				isCompare = false;
				break;
			}
			continue;
		}

		if (eventTable->object == nullptr || eventTable->event == nullptr)
		{
			if (eventTable->event != nullptr)
			{
				delete eventTable->event;
				eventTable->event = nullptr;
			}

			delete eventTable;
			eventTable = nullptr;

			if (eventAPI->eventQueue.empty())
			{
				isCompare = false;
				break;
			}
			continue;
		}

		if (!eventTable->event->isCondense())
		{
			return eventTable;
		}

		break;
	}

	std::size_t number_ = 0;

	EventTable* eventTableNext = nullptr;

	//获取下一事件
	while (true)
	{
		if (eventAPI->eventQueue.empty())
		{
			isCompare = false;
			break;
		}

		eventTableNext = eventAPI->eventQueue.peek();

		if (eventTableNext == nullptr)
		{
			eventAPI->eventQueue.read();
			continue;
		}

		if (eventTableNext->object == nullptr)
		{
			if (eventTableNext->event != nullptr)
			{
				delete eventTableNext->event;
			}
			delete eventTableNext;
			eventAPI->eventQueue.read();
			continue;
		}

		break;
	}

	while (isCompare)
	{
		//比较两个事件是否是相同，如果相同就压缩为同一事件
		if ((eventTable->object) == (eventTableNext->object))
		{
			if (eventTableNext->event->type() == eventTable->event->type())
			{
				//删除下一件事件
				eventAPI->eventQueue.read();
				delete eventTableNext->event;
				delete eventTableNext;
				eventTableNext = nullptr;

				//检测循环次数是否超过指定值
				if ((number != 0))
				{
					number_++;
					if (number_ >= number)
					{
						break;
					}
				}

				//重新获取下一事件
				while (true)
				{
					if (eventAPI->eventQueue.empty())
					{
						isCompare = false;
						break;
					}

					eventTableNext = eventAPI->eventQueue.peek();

					if (eventTableNext == nullptr)
					{
						eventAPI->eventQueue.read();
						continue;
					}

					if (eventTableNext->object == nullptr)
					{
						if (eventTableNext->event != nullptr)
						{
							delete eventTableNext->event;
						}
						delete eventTableNext;
						eventAPI->eventQueue.read();
						continue;
					}

					break;
				}
			}
		}
		else
		{
			break;
		}
	}

	return eventTable;
}