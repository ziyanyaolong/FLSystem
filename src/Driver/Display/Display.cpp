#include "Display.h"

FLSYSTEM::Display::~Display()
{
#ifdef FLSYSTEM_ENABLE_LVGL_8

#endif
}

bool FLSYSTEM::Display::registerDisplay(DisplayAPI* api)
{
	auto tableSize = displayList.getTable().size();
	displayList.getTable().lock();
	for (std::size_t i = 0; i < tableSize; i++)
	{
		if (displayList.getTable()[i] == api)
		{
			displayList.getTable().unlock();
			return false;
		}
	}
	displayList.getTable().unlock();
	displayList.reg(api);

	return true;
}

void FLSYSTEM::Display::loop()
{
	auto tableSize = displayList.getTable().size();

	for (std::size_t i = 0; i < tableSize; i++)
	{
		if (displayList.getTable()[i]->isBegin())
		{
			displayList.getTable()[i]->begin();
		}

		displayList.getTable()[i]->loop();
	}

	/*for (auto &&i : registerMapTable)
	{
	  auto display = i.second;

	  if (display == nullptr)
		continue;

	  if (!display->isInit())
	  {
		display->processInit();

  #ifdef FLSYSTEM_ENABLE_LVGL_8
		
  #endif
		Kernel::processSchedule.CreateThread(display);
	  }
	}*/
}