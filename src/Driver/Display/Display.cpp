#include "Display.h"

FLSYSTEM::Display::~Display()
{
#ifdef FLSYSTEM_ENABLE_LVGL_8

#endif
}

void FLSYSTEM::Display::loop()
{
	/*for (auto &&i : registerMapTable)
	{
	  auto display = i.second;

	  if (display == nullptr)
		continue;

	  if (!display->isInit())
	  {
		display->processInit();

  #ifdef FLSYSTEM_ENABLE_LVGL_8
		switch (display->displayData.cacheMode)
		{
		case FLSYSTEM::DisplayAPI::CacheMode::ONE_CACHE:
		  if (display->displayDriver.buf_1 == nullptr)
			display->displayDriver.buf_1 = new lv_color_t[display->displayData.cache];
		  break;

		case FLSYSTEM::DisplayAPI::CacheMode::TWO_CACHE:

		  if (display->displayDriver.buf_1 == nullptr)
			display->displayDriver.buf_1 = new lv_color_t[display->displayData.cache];

		  if (display->displayDriver.buf_2 == nullptr)
			display->displayDriver.buf_2 = new lv_color_t[display->displayData.cache];
		  break;

		default:
		  continue;
		  break;
		}

		if (display->displayDriver.disp_buf == nullptr)
		  display->displayDriver.disp_buf = new lv_disp_draw_buf_t;
		if (display->displayDriver.disp_drv == nullptr)
		  display->displayDriver.disp_drv = new lv_disp_drv_t;

		lv_disp_draw_buf_init(display->displayDriver.disp_buf, display->displayDriver.buf_1, display->displayDriver.buf_2, display->displayData.cache);
		lv_disp_drv_init(display->displayDriver.disp_drv);
		display->displayDriver.disp_drv->flush_cb = &FLSYSTEM::DisplayAPI::_runFunFlush_;
		display->displayDriver.disp_drv->draw_buf = display->displayDriver.disp_buf;
		display->displayDriver.disp_drv->full_refresh = display->displayData.fullRefresh;
		display->displayDriver.disp_drv->sw_rotate = display->displayData.swRotate;
		display->displayDriver.disp_drv->hor_res = display->displayData.screenWidget;
		display->displayDriver.disp_drv->ver_res = display->displayData.screenHight;
		display->displayDriver.disp_drv->dpi = display->displayData.dpi;
		display->displayDriver.disp_drv->rotated = display->displayData.rotated;
		display->displayDriver.disp_drv->antialiasing = display->displayData.antialiasing;
		display->displayDriver.disp_drv->screen_transp = display->displayData.screenTransp;
		display->displayDriver.disp_drv->user_data = static_cast<void *>(display);
		display->displayDriver.disp = lv_disp_drv_register(display->displayDriver.disp_drv);
  #endif
		Kernel::processSchedule.CreateThread(display);
	  }
	}*/
}

