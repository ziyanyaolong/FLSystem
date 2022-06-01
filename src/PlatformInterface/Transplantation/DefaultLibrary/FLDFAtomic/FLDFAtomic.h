#ifndef FLSYSTEM_FLDFATOMIC_H
#define FLSYSTEM_FLDFATOMIC_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

#include "../../FLTRInclude.h"

#define FLSYSTEM_3RD_ATOMIC

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	template<typename _Ty>
	class FLDFAtomic : public AtomicInterface<_Ty>
	{
	private:
		std::atomic<_Ty> _atomic;

	public:
		explicit FLDFAtomic<_Ty>(FLLockType type) : AtomicInterface<_Ty>(type){}
		virtual ~FLDFAtomic<_Ty>() {}

		inline virtual  _Ty load() noexcept override { return _atomic.load(); }
		inline virtual bool compare_exchange_strong(_Ty& _Expected, const _Ty _Desired) noexcept override { return _atomic.compare_exchange_strong(_Expected, _Desired); }
		inline virtual void store(_Ty data) noexcept override { _atomic.store(data); }

		inline virtual void* getLock() override { return &_atomic; }
	};
}

#endif

#endif
