#ifndef FLSYSTEM_STL_BASIC_H
#define FLSYSTEM_STL_BASIC_H

#include "../../../IPC/Lock/FLReadWriteLock/FLReadWriteLock.h"
#include "../../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
	class STL_Basic : public GC_API
	{
	public:
		enum class Mode
		{
			NoLock,
			HaveLock
		};

	private:
		FLReadWriteLock* look = nullptr;
		Mode _mode_;

	protected:
		FLInline void setWrite()
		{
			if (look)
			{
				look->lockWrite();
			}
		}

		FLInline void resetWrite()
		{
			if (look)
			{
				look->unlockWrite();
			}
		}

		FLInline void setRead()
		{
			if (look)
			{
				look->lockRead();
			}
		}

		FLInline void resetRead()
		{
			if (look)
			{
				look->unlockRead();
			}
		}

		FLInline void setAlgorithm()
		{
			setWrite();
		}

		FLInline void resetAlgorithm()
		{
			resetWrite();
		}

	public:
		FLInline void lock()
		{
			setAlgorithm();
		}

		FLInline void unlock()
		{
			resetAlgorithm();
		}

		STL_Basic(Mode mode = Mode::HaveLock)
			: GC_API(), _mode_(mode)
		{
			switch (mode)
			{
			case FLSYSTEM::STL_Basic::Mode::NoLock:
				break;
			case FLSYSTEM::STL_Basic::Mode::HaveLock:
				look = new FLReadWriteLock();
				break;
			default:
				break;
			}
		}
		virtual ~STL_Basic() 
		{
			if (look)
			{
				look->deleteLater();
			}
		}
	};
}

#endif