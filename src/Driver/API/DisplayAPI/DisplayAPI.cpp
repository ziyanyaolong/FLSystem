#include "DisplayAPI.h"

FLSYSTEM::DisplayAPI::~DisplayAPI()
{
	if (displayData)
	{
		delete displayData;
		displayData = nullptr;
	}
}

FLSYSTEM::DisplayAPI::DisplayAPI(DisplayData* data, FLSYSTEM::FLObject* object, const std::string& name ) : Driver_API(object, name)
{
	displayData = this->createDisplayData();
	if (data)
	{
		displayData = data;
	}
}

FLSYSTEM::DisplayAPI::DisplayAPI(uint16_t screenWidget, uint16_t screenHight, uint32_t rotated, FLSYSTEM::FLObject* object, const std::string& name) : Driver_API(object, name)
{
	displayData = this->createDisplayData();
	displayData->screenWidget = screenWidget;
	displayData->screenHight = screenHight;
	displayData->rotated = rotated;

}
