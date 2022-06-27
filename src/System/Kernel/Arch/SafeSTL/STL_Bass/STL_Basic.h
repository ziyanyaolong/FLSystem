#ifndef FLSYSTEM_STL_BASIC_H
#define FLSYSTEM_STL_BASIC_H

#include "../../../IPC/Lock/FLLock/FLLock.h"

namespace FLSYSTEM
{
	class STL_Basic
	{
	private:
		FLLock writeLook;
		FLLock readLook;

	protected:
		void setWrite()
		{
			while (true)
			{
				if (writeLook.isLocking() || readLook.isLocking())
				{
					continue;
				}

				writeLook.lock();

				if (!writeLook.isLocking() || readLook.isLocking())
				{
					writeLook.unlock();
					continue;
				}

				break;
			}
		}

		void resetWrite()
		{
			writeLook.unlock();
		}

		void setRead()
		{
			while (true)
			{
				if (writeLook.isLocking())
				{
					continue;
				}
				else if (readLook.isLocking())
				{
					break;
				}

				readLook.lock();

				if (!readLook.isLocking() || writeLook.isLocking())
				{
					readLook.unlock();
					continue;
				}
				break;
			}
		}

		void resetRead()
		{
			readLook.unlock();
		}

		void setAlgorithm()
		{
			setWrite();
		}

		void resetAlgorithm()
		{
			resetWrite();
		}

	public:
		void lock()
		{
			setAlgorithm();
		}

		void unlock()
		{
			resetAlgorithm();
		}
	};
}

#endif