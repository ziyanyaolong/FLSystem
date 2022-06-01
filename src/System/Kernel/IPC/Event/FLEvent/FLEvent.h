#ifndef FLSYSTEM_FLEVENT_H
#define FLSYSTEM_FLEVENT_H

#include "../../../../../PlatformInterface/PlatformInterface.h"
#include "../../Lock/FLLock/FLLock.h"

#define FLRegisterEvent(name) namespace FLSYSTEM { namespace FLEventTypes { const FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType name = FLSYSTEM::FLEvent::registerEventType(); } }

namespace FLSYSTEM
{
	namespace FLEventTypes
	{
	}

	class FLEvent
	{
	public:
		enum Type : FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType
		{
			Normal = 0,
			ExitLoop,
			EndEvent,
			RegiserEvent,
		};

    private:
		FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType _type = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType>(FLEvent::Type::Normal);
		static FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType _userType;
		void* userData_ = nullptr;
		bool _isCondense;

    public:
        FLEvent();
		FLEvent(FLEvent::Type type, bool isCondense = false) : FLEvent()
		{
			_type = static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType>(type);
			_isCondense = isCondense;
		}

		FLEvent(FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType type, bool isCondense = false) : FLEvent()
		{
			_type = type;
			_isCondense = isCondense;
		}

        virtual ~FLEvent();

		inline const FLEvent::Type type() { return static_cast<FLEvent::Type>(_type); }

		static FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType registerEventType(FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType replacementValue = 0)
		{
			if (replacementValue != 0)
			{
				FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType pULL = (replacementValue + static_cast<FLSYSTEM_TRANSPLANTATION_TYPE::FLEventSizeType>(Type::EndEvent));
				if (_userType < pULL)
					_userType = pULL;

				return pULL;
			}

			return (++_userType);
		}

		inline bool operator==(const FLEvent& event)
		{
			if (this->_type == event._type)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		inline void setUserData(void* userData)
		{
			userData_ = userData;
		}

		inline void* getUserData() const
		{
			return userData_;
		}

		inline bool isCondense()
		{
			return _isCondense;
		}
	};
}

#endif