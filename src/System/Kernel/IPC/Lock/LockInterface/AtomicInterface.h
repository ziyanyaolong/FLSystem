#ifndef FLSYSTEM_ATOMIC_INTERFACE_H
#define FLSYSTEM_ATOMIC_INTERFACE_H

#include "LockBaseInterface.h"

namespace FLSYSTEM
{
	template <typename _Ty>
	FLInterface AtomicInterface : public LockBaseInterface
	{
	protected:
		explicit AtomicInterface<_Ty>(FLLockType type) : LockBaseInterface(type) {}

	public:
		virtual ~AtomicInterface<_Ty>() {}

		virtual  _Ty load() noexcept = 0;
		virtual bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired) noexcept = 0;
		virtual void store(_Ty data) noexcept = 0;

	};
}

#endif
