#include "FLObject.h"

FLSYSTEM::FLObject::FLObject(FLObject *parent, const std::string &name) : FLObject(name)
{
    if (parent != nullptr)
    {
        _parent = parent;

        if (parent->childrenList == nullptr)
            parent->childrenList = new FLObjectList();

        parent->childrenList->push_back(this);
    }
    
    isDelete = false;
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

void FLSYSTEM::FLObject::deleteLater()

{
    if (!isDelete)
        isDelete = true;
}

bool FLSYSTEM::FLObject::eventFilter(FLObject *watched, FLEvent *event)
{
    return false;
}

bool FLSYSTEM::FLObject::event(FLEvent *event)
{
    return false;
}