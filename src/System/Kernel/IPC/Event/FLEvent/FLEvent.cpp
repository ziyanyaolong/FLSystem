#include "FLEvent.h"

FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType FLSYSTEM::FLEvent::_userType = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType>(Type::EndEvent);

//FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType FLSYSTEM::FLEvent::registerEventType(FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType replacementValue)
//{
//	if (replacementValue != 0)
//	{
//		FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType pULL = (replacementValue + static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType>(Type::EndEvent));
//		if (_userType < pULL)
//			_userType = pULL;
//
//		return pULL;
//	}
//
//	return (++_userType);
//}

FLSYSTEM::FLEvent::FLEvent() : GC_API()
{
}

FLSYSTEM::FLEvent::~FLEvent()
{
}