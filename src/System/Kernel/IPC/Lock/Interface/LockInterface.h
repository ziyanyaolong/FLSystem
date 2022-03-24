#ifndef FLSYSTEM_LOCKINTERFACE_H
#define FLSYSTEM_LOCKINTERFACE_H

namespace FLSYSTEM
{
	class LockInterface
	{
	public:
		explicit LockInterface() {}
		virtual ~LockInterface() {}

		virtual void lock() = 0;
		virtual void unlock() = 0;
		virtual bool isLocking() = 0;

	};
}

#endif
