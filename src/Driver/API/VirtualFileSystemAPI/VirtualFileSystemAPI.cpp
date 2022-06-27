#include "VirtualFileSystemAPI.h"

FLSYSTEM::VirtualFileSystemAPI::VirtualFileSystemAPI(const char* driver)
	: Driver_API(std::string(driver) + ":/")
{
}

FLSYSTEM::VirtualFileSystemAPI::VirtualFileSystemAPI(const std::string& driver)
	: Driver_API(driver + ":/")
{
}

FLSYSTEM::VirtualFileSystemAPI::~VirtualFileSystemAPI()
{
}