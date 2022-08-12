#include "ThreadAPI.h"

FLSYSTEM::ThreadAPI::ThreadAPI(FLObject* parent, const std::string& name) : EventAPI(parent, name)
{
	isThread = true;
}

int FLSYSTEM::ThreadAPI::exit()
{
	_lock.lockWrite();
	_threadData_.isExit = true;
	_lock.unlockWrite();
	return 0;
}

void FLSYSTEM::ThreadAPI::start()
{
	if (!isStart())
	{
		_lock.lockWrite();
		_threadData_.isStart = true;
		_lock.unlockWrite();
		this->run();
	}
}

bool FLSYSTEM::ThreadAPI::isExit()
{
	_lock.lockRead();
	bool temp = _threadData_.isExit;
	_lock.unlockRead();
	return temp;
}

bool FLSYSTEM::ThreadAPI::isStart()
{
	_lock.lockRead();
	bool temp = _threadData_.isStart;
	_lock.unlockRead();
	return temp;
}

void FLSYSTEM::ThreadAPI::setRunTimeDelay(unsigned long long time)
{
	_lock.lockWrite();
	_threadConfig_.runTimeDelay = time;
	_lock.unlockWrite();
}

void FLSYSTEM::ThreadAPI::setPriority(unsigned long priority)
{
	_lock.lockWrite();
	_threadConfig_.priority = priority;
	_lock.unlockWrite();
}

void FLSYSTEM::ThreadAPI::setStackDepth(unsigned long stackDepth)
{
	_lock.lockWrite();
	_threadConfig_.stackDepth = stackDepth;
	_lock.unlockWrite();
}

void FLSYSTEM::ThreadAPI::shallowSleep(int64_t time)
{
	_lock.lockWrite();
	_threadData_.shallowSleepTime = time;
	_lock.unlockWrite();
}

void FLSYSTEM::ThreadAPI::exec()
{
	FLSYSTEM_TRANSPLANTATION_TYPE::ThreadDelayConfig config;
	_lock.lockRead();
	config.threadConfig = &(this->_threadConfig_);
	config.time = this->_threadConfig_.runTimeDelay;
	_lock.unlockRead();

	while (!isExit())
	{
		_lock.lockRead();
		if (config.time != this->_threadConfig_.runTimeDelay)
		{
			config.time = this->_threadConfig_.runTimeDelay;
		}
		_lock.unlockRead();

		FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(&config);

		_lock.lockRead();
		if (_threadData_.shallowSleepTime >= _threadConfig_.runTimeDelay)
		{
			_lock.unlockRead();
			_lock.lockWrite();
			_threadData_.shallowSleepTime -= _threadConfig_.runTimeDelay;
			_lock.unlockWrite();
		}
		else if ((_threadData_.shallowSleepTime < _threadConfig_.runTimeDelay) && (_threadData_.shallowSleepTime > 0))
		{
			_lock.unlockRead();
			_lock.lockWrite();
			_threadData_.shallowSleepTime = 0;
			_lock.unlockWrite();
		}
		else
		{
			_lock.unlockRead();
			this->runInEventLoop();
		}

		this->process();
	}
}

bool FLSYSTEM::ThreadAPI::sleep(ThreadAPI* threadPointer, int64_t time)
{
	if (threadPointer == nullptr)
	{
		return false;
	}
	FLSYSTEM_TRANSPLANTATION_TYPE::ThreadDelayConfig config;
	threadPointer->_lock.lockRead();
	config.threadConfig = &(threadPointer->_threadConfig_);
	threadPointer->_lock.unlockRead();
	config.time = time;
	FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(&config);
	return true;
}

void FLSYSTEM::ThreadAPI::sleep(int64_t time)
{
	FLSYSTEM_TRANSPLANTATION_TYPE::ThreadDelayConfig config;
	this->_lock.lockRead();
	config.threadConfig = &(this->_threadConfig_);
	this->_lock.unlockRead();
	config.time = time;
	FLSYSTEM_TRANSPLANTATION_INSTANCE->threadDelay(&config);
}

void FLSYSTEM::ThreadAPI::exitOut()
{
	_lock.lockWrite();
	_threadData_.isEnd = true;
	_lock.unlockWrite();
}

void FLSYSTEM::ThreadAPI::process()
{
	EventCore::process(static_cast<EventAPI*>(this));
}