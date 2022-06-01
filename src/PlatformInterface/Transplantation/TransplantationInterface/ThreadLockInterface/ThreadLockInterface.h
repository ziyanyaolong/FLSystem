#ifndef FLSYSTEM_THREADLOCKINTERFACE_H
#define FLSYSTEM_THREADLOCKINTERFACE_H

namespace FLSYSTEM
{
	template <typename _Ty>
	class AtomicInterface;

	class MutexInterface;
	class SemaphoreInterface;
	enum class FLLockType;

	template <typename _TI>
	class ThreadLockInterface
	{
	private:
		_TI* getTI()
		{
			return static_cast<_TI*>(this);
		}

	protected:
		explicit ThreadLockInterface<_TI>() {}

	public:
		virtual ~ThreadLockInterface<_TI>() {}

		template <typename _Ty>
		inline AtomicInterface<_Ty>* createAtomic(FLLockType type)
		{
			return this->getTI()->template fl_createAtomic<_Ty>(type);
		}

		inline MutexInterface* createMutex(FLLockType type)
		{
			return this->getTI()->fl_createMutex(type);
		}

		inline SemaphoreInterface* createSemaphore(FLLockType type, unsigned long long maxCount, unsigned long long initialCount)
		{
			return this->getTI()->fl_createSemaphore(type, maxCount, initialCount);
		}
	};
}

#endif
