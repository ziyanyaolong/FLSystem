#ifndef FLSYSTEM_FLOBJECT_H
#define FLSYSTEM_FLOBJECT_H

#include "../../API/BaseAPI/BaseAPI.h"
#include "../SafeSTL/FLVector/FLVector.h"
#include "../FLRTTI/FLRTTI.h"

namespace FLSYSTEM
{
    class FLEvent;
    class FLObject : virtual public BaseAPI, public FLRTTI
    {
    private:
        typedef FLVector<FLObject *> FLObjectList;
        friend class EventCore;
        FLObjectList *eventFilters = nullptr;
        FLObjectList *childrenList = nullptr;
        FLObject *_parent = nullptr;

    protected:
        bool isThread = false;
		virtual bool event(FLEvent* event);
		virtual bool eventFilter(FLObject* watched, FLEvent* event);

    public:
        FLObject(FLObject *parent = nullptr, const std::string &name = std::string(""));
		FLObject(const std::string& name);
		virtual ~FLObject();

		void setParent(FLObject* parent);

        FLInline FLObject* getParent() { return _parent; }

		FLInline void installEventFilter(FLObject* object)
		{
			if (object->eventFilters == nullptr)
			{
				object->eventFilters = new FLObjectList(FLObjectList::Mode::NoLock);
			}

			object->eventFilters->push_back(this);
		}

		FLInline bool isInstallEventFilter()
		{
			if (eventFilters == nullptr)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
    };
}

#endif