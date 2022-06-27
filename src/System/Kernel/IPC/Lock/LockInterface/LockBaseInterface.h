#ifndef FLSYSTEM_LOCKBASEINTERFACE_H
#define FLSYSTEM_LOCKBASEINTERFACE_H

#include "../../../../../PlatformInterface/FLDefine.h"

#define FLSYSTEM_3RD_STDINT
#include "../../../../../PlatformInterface/3rdInclude.h"

namespace FLSYSTEM
{
	enum class FLLockType
	{
		UnknowType = 0x0,
		Atomic,
		Binary,
		Counting,
		Mutex,
		RecursiveMutex
	};

	class LockBaseInterface
	{
	private:
		FLLockType _type;

	protected:
		explicit LockBaseInterface(FLLockType type) { _type = type; }

	public:
		virtual ~LockBaseInterface() {}

		inline const FLLockType& typeGet()
		{
			return _type;
		}

		inline virtual void* getLock() 
		{ 
			return nullptr; 
		}
		
		template<typename _Ty>
		inline _Ty getLockFor()
		{
			return static_cast<_Ty>(this->getLock());
		}
	};
}

#endif
