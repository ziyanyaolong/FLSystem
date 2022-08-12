#ifndef FLSYSTEM_FLFRATOMIC_H
#define FLSYSTEM_FLFRATOMIC_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

#include "../../FLTRInclude.h"
#include "../FLFRMutex/FLFRMutex.h"

#define FLSYSTEM_3RD_FREERTOS

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	template<typename _Ty>
	class FLFRAtomic : public AtomicInterface<_Ty>
	{
	private:
		FLFRMutex* _aLock;
		_Ty _storedValue = _Ty();

	public:
		explicit FLFRAtomic(FLLockType type) : AtomicInterface<_Ty>(type), _aLock(new FLFRMutex(FLLockType::Mutex)) {}
		
		virtual ~FLFRAtomic() 
		{
			delete _aLock;
		}

		inline virtual _Ty load() noexcept
		{
			_aLock->lock();
			auto tempData = _storedValue;
			_aLock->unlock();
			return tempData;
		}

		inline virtual bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired) noexcept
		{
			_aLock->lock();
			if (_storedValue == _Expected)
			{
				_storedValue = _Desired;
				_aLock->unlock();
				return true;
			}
			else
			{
				_Expected = _storedValue;
				_aLock->unlock();
				return false;
			}
		}

		inline virtual void store(_Ty data) noexcept
		{
			_aLock->lock();
			_storedValue = data;
			_aLock->unlock();
		}

	};
}

#endif

#endif