#ifndef FLSYSTEM_STL_BASIC_H
#define FLSYSTEM_STL_BASIC_H

#include "../../Kernel/IPC/Lock/FLLock/FLLock.h"

namespace FLSYSTEM
{
	class STL_Basic
	{
	private:
		FLLock isLookingAtAlgorithm;
		FLLock isLookingAtWrite;
		FLLock isLookingAtRead;

	protected:
		void setWrite()
		{
			while (true)
			{
				if (isLookingAtAlgorithm.isLocking() || isLookingAtRead.isLocking())
				{
					continue;
				}
				isLookingAtWrite.lock();
				if (isLookingAtAlgorithm.isLocking() || isLookingAtRead.isLocking())
				{
					isLookingAtWrite.unlock();
					continue;
				}
				break;
			}
		}

		void resetWrite()
		{
			isLookingAtWrite.unlock();
		}

		void setRead()
		{
			if (isLookingAtRead.isLocking())
			{
				return;
			}

			while (true)
			{
				if (isLookingAtAlgorithm.isLocking() || isLookingAtWrite.isLocking())
				{
					continue;
				}
				isLookingAtRead.lock();
				if (isLookingAtAlgorithm.isLocking() || isLookingAtWrite.isLocking())
				{
					isLookingAtRead.unlock();
					continue;
				}
				break;
			}
		}

		void resetRead()
		{
			isLookingAtRead.unlock();
		}

		void setAlgorithm()
		{
			while (true)
			{
				if (isLookingAtRead.isLocking() || isLookingAtWrite.isLocking())
				{
					continue;
				}
				isLookingAtAlgorithm.lock();
				if (isLookingAtRead.isLocking() || isLookingAtWrite.isLocking())
				{
					isLookingAtAlgorithm.unlock();
					continue;
				}
				break;
			}
		}

		void resetAlgorithm()
		{
			isLookingAtAlgorithm.unlock();
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