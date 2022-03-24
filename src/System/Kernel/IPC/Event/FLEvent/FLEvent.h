#ifndef FLSYSTEM_FLEVENT_H
#define FLSYSTEM_FLEVENT_H

#include "../../../../../PlatformInterface/PlatformInterface.h"

#define FLRegisterEvent(name) namespace FLSYSTEM { namespace FLEventTypes { const FLEventSizeType name = FLSYSTEM::FLEvent::registerEventType(); } }

namespace FLSYSTEM
{
	namespace FLEventTypes
	{
	}

	class FLEvent
	{
	public:
		enum Type : FLEventSizeType
		{
			Normal = 0,
			ExitLoop,
			EndEvent,
			RegiserEvent,
		};

    private:
		FLEventSizeType _type = static_cast<FLEventSizeType>(FLEvent::Type::Normal);
		static FLEventSizeType _userType;
		void* userData_ = nullptr;

    public:
        FLEvent();
        FLEvent(FLEvent::Type type) : _type(type) { FLEvent(); }
		FLEvent(FLEventSizeType type) : _type(type) { FLEvent(); }
        virtual ~FLEvent();

		const FLEvent::Type type() { return static_cast<FLEvent::Type>(_type); }

		static FLEventSizeType registerEventType(FLEventSizeType replacementValue = 0)
		{
			if (replacementValue != 0)
			{
				FLEventSizeType pULL = (replacementValue + static_cast<FLEventSizeType>(Type::EndEvent));
				if (_userType < pULL)
					_userType = pULL;

				return pULL;
			}

			return (++_userType);
		}

		bool operator==(const FLEvent& event)
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

		void setUserData(void* userData)
		{
			userData_ = userData;
		}

		void* getUserData() const
		{
			return userData_;
		}
	};
}

#endif