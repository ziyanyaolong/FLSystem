#include "ExternalStorage.h"

FLSYSTEM::ExternalStorage::ExternalStorage(FLObject* parent, const std::string& name) : Driver_API(parent, name)
{
}

FLSYSTEM::ExternalStorage::~ExternalStorage()
{
}

void FLSYSTEM::ExternalStorage::begin()
{
}

void FLSYSTEM::ExternalStorage::loop()
{
	//for (auto &&i : registerMapTable)
	//{
		//auto api = i.second;
		// if(!api->isBegin())
			// ProcessManagement::taskRequest(api, ProcessScheduleAPI::Request::Create);
	//}
}