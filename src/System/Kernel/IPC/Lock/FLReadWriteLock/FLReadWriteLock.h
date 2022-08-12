#ifndef FLSYSTEM_FLREADWRITELOCK_H
#define FLSYSTEM_FLREADWRITELOCK_H

#include "../FLMutex/FLMutex.h"
//#include "../../../Arch/SafeSTL/FLQueue/FLQueue.h"
#include "../../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
	class FLReadWriteLock : public GC_API
	{
	private:
		enum class ReadWriteMode
		{
			ReadFirst,
			WriteFirst,
			Equity
		};

		struct FLReadWriteLockData
		{
			FLReadWriteLockData() 
			{
				this->isWrite = false;
				this->isRead = false;
				this->equityMode = false;
			}

			bool isWrite   : 1;
			bool isRead    : 1;
			bool equityMode: 1;
			bool : 1;
			bool : 1;
			bool : 1;
			bool : 1;
			bool : 1;
			unsigned int read_lock_number = 0;
			//FLQueue<unsigned int>* lockQueue = nullptr;
		};

		FLReadWriteLockData _rwld;
		ReadWriteMode _mode;
		ReadWriteMode _modeEquity;
		FLMutex* readLock;
		FLMutex* writeLock;
		FLMutex* data_lock;
		
	public:
		bool isWrite()
		{
			return _rwld.isWrite;
		}

		bool isRead()
		{
			return _rwld.isRead;
		}
		explicit FLReadWriteLock(ReadWriteMode mode = ReadWriteMode::WriteFirst) : GC_API(), _mode(mode), _modeEquity(_mode)
		{
			readLock = new FLMutex(FLLockType::Mutex);
			writeLock = new FLMutex(FLLockType::Mutex);
			data_lock = new FLMutex(FLLockType::Mutex);
		}
		virtual ~FLReadWriteLock() 
		{
			if (readLock)
			{
				readLock->deleteLater();
			}

			if (writeLock)
			{
				writeLock->deleteLater();
			}

			if (data_lock)
			{
				data_lock->deleteLater();
			}
		}

		FLInline void lockRead()
		{
			switch (_modeEquity)
			{
			case FLSYSTEM::FLReadWriteLock::ReadWriteMode::ReadFirst:
				data_lock->lock();

				if (!_rwld.isRead)
				{
					_rwld.isRead = true;
					readLock->lock();
				}

				_rwld.read_lock_number++;

				while (_rwld.isWrite)
				{
					data_lock->unlock();
					data_lock->lock();
				}

				data_lock->unlock();

				break;
			case FLSYSTEM::FLReadWriteLock::ReadWriteMode::WriteFirst:
				while (true)
				{
					data_lock->lock();
					if (_rwld.isWrite)
					{
						data_lock->unlock();
						continue;
					}
					else if (_rwld.isRead)
					{
						_rwld.read_lock_number++;
						break;
					}

					readLock->lock();

					if (!_rwld.isRead)
					{
						_rwld.isRead = true;
					}

					if (_rwld.isWrite)
					{
						_rwld.isRead = false;
						data_lock->unlock();
						readLock->unlock();
						continue;
					}

					_rwld.read_lock_number++;

					break;
				}
				data_lock->unlock();
				break;

			case FLSYSTEM::FLReadWriteLock::ReadWriteMode::Equity:
				if (!_rwld.equityMode)
				{
					_modeEquity = ReadWriteMode::WriteFirst;
				}
				else
				{
					_modeEquity = ReadWriteMode::ReadFirst;
				}
				_rwld.equityMode = !_rwld.equityMode;
				this->lockRead();
				break;

			default:
				break;
			}
		}

		FLInline void lockWrite()
		{
			switch (_modeEquity)
			{
			case FLSYSTEM::FLReadWriteLock::ReadWriteMode::ReadFirst:
				writeLock->lock();

				while (true)
				{
					data_lock->lock();
					if (_rwld.isRead)
					{
						data_lock->unlock();
						continue;
					}

					_rwld.isWrite = true;

					if (_rwld.isRead)
					{
						continue;
					}

					data_lock->unlock();

					break;
				}

				break;
			case FLSYSTEM::FLReadWriteLock::ReadWriteMode::WriteFirst:
				data_lock->lock();
				while (_rwld.isWrite)
				{
					data_lock->unlock();
					data_lock->lock();
				}
				_rwld.isWrite = true;

				writeLock->lock();

				while (_rwld.isRead)
				{
					data_lock->unlock();
					data_lock->lock();
				}
				data_lock->unlock();

				break;

			case FLSYSTEM::FLReadWriteLock::ReadWriteMode::Equity:
				if (!_rwld.equityMode)
				{
					_modeEquity = ReadWriteMode::WriteFirst;
				}
				else
				{
					_modeEquity = ReadWriteMode::ReadFirst;
				}
				_rwld.equityMode = !_rwld.equityMode;
				this->lockWrite();
				break;
			default:
				break;
			}
		}

		FLInline void unlockRead() 
		{
			data_lock->lock();
			if (_rwld.read_lock_number > 0)
			{
				_rwld.read_lock_number--;

				if (_rwld.read_lock_number == 0)
				{
					readLock->unlock();
					_rwld.isRead = false;
					data_lock->unlock();
				}
				else
				{
					data_lock->unlock();
				}
			}
			else
			{
				data_lock->unlock();
			}
		}

		FLInline void unlockWrite()
		{
			writeLock->unlock();

			data_lock->lock();
			_rwld.isWrite = false;
			data_lock->unlock();
		}
	};
}

#endif
