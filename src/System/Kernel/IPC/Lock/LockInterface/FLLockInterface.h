#ifndef FLSYSTEM_FLLOCKINTERFACE_H
#define FLSYSTEM_FLLOCKINTERFACE_H

namespace FLSYSTEM
{
	enum class FLLockType;
	class FLLockInterface
	{
	private:
		friend class FLLock;

	protected:
		explicit FLLockInterface() {}

		virtual bool lock_FLLock() = 0;
		virtual void unlock_FLLock() = 0;
		virtual bool isLocking_FLLock() = 0;
		virtual FLLockType typeGet() = 0;

	public:
		virtual ~FLLockInterface() {}

	};
}

#endif
