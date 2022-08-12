#include "FLObject.h"

FLSYSTEM::FLObject::FLObject(FLObject* parent, const std::string& name) : FLObject(name)
{
	this->setParent(parent);
}

FLSYSTEM::FLObject::FLObject(const std::string& name) : BaseAPI(name), FLRTTI()
{

}

FLSYSTEM::FLObject::~FLObject()
{
	if (eventFilters)
	{
		eventFilters->clear();
		delete eventFilters;
		eventFilters = nullptr;
	}

	if (childrenList)
	{
		childrenList->clear();
		delete childrenList;
		childrenList = nullptr;
	}
}

void FLSYSTEM::FLObject::setParent(FLObject* parent)
{
	if (_parent != nullptr)
	{
		_parent->childrenList->lock();
		for (auto i = _parent->childrenList->begin(); i != _parent->childrenList->end(); i++)
		{
			if (*i == this)
			{
				_parent->childrenList->erase(i);
				break;
			}
		}
		_parent->childrenList->unlock();
	}

	_parent = parent;

	if (parent == nullptr)
	{
		return;
	}
	else if (parent->childrenList == nullptr)
	{
		parent->childrenList = new FLObjectList(FLObjectList::Mode::NoLock);
		
	}
	else
	{
		parent->childrenList->lock();
		for (auto&& i = parent->childrenList->begin(); i != parent->childrenList->end(); i++)
		{
			if (*i == this)
			{
				parent->childrenList->unlock();
				return;
			}
		}
		parent->childrenList->unlock();
	}

	parent->childrenList->push_back(this);
}

bool FLSYSTEM::FLObject::eventFilter(FLObject* watched, FLEvent* event)
{
	return false;
}

bool FLSYSTEM::FLObject::event(FLEvent* event)
{
	return false;
}