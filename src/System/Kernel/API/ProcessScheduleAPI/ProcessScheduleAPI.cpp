#include "ProcessScheduleAPI.h"

FLSYSTEM::ProcessScheduleAPI::~ProcessScheduleAPI()
{
}

FLSYSTEM::ProcessScheduleAPI::ProcessScheduleAPI(FLObject* object, const std::string& name) 
	: ThreadAPI(object, name) 
{
}

bool FLSYSTEM::ProcessScheduleAPI::isBegin()
{
	this->getLock().lockRead();
	auto temp = processConfig.isBegin;
	this->getLock().unlockRead();
	return temp;
}
bool FLSYSTEM::ProcessScheduleAPI::isInit()
{
	this->getLock().lockRead();
	auto temp = processConfig.isInit;
	this->getLock().unlockRead();
	return temp;
}
unsigned long long FLSYSTEM::ProcessScheduleAPI::getPID()
{
	this->getLock().lockRead();
	auto temp = processConfig.PID;
	this->getLock().unlockRead();
	return temp;
}