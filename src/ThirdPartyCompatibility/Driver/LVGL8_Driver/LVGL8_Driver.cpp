#include "LVGL8_Driver.h"

#ifdef FLSYSTEM_ENABLE_LVGL

FLSYSTEM::LVGL8_Driver::LVGL8_Driver(DisplayData* data, FLObject* object, const std::string& name) : DisplayAPI(data, object, name)
{
}

FLSYSTEM::LVGL8_Driver::LVGL8_Driver(uint16_t screenWidget, uint16_t screenHight, uint32_t rotated, FLObject* object, const std::string& name) : DisplayAPI(screenWidget, screenHight, rotated, object, name)
{
}

FLSYSTEM::LVGL8_Driver::~LVGL8_Driver()
{
}

bool FLSYSTEM::LVGL8_Driver::setDesktopBackground(const lv_img_dsc_t * DBs)
{
	desktopBackground = *DBs;
	if (DBs != nullptr)
	{
		if (DB)
		{
			lv_obj_del(DB);
		}
		DB = lv_img_create(lv_scr_act());
		lv_img_set_src(DB, &desktopBackground);
		lv_obj_set_size(DB, this->getDisplayData<LVGL_DisplayData>()->screenWidget, this->getDisplayData<LVGL_DisplayData>()->screenHight);
		lv_obj_set_pos(DB, 0, 0);
		lv_obj_move_background(DB);
		return true;
	}
	else
		return false;
}

int FLSYSTEM::LVGL8_Driver::regIn()
{
	switch (this->getDisplayData<LVGL_DisplayData>()->cacheMode)
	{
	case FLSYSTEM::LVGL8_Driver::CacheMode::ONE_CACHE:
		if (lvgl_displayDriver.buf_1 == nullptr)
			lvgl_displayDriver.buf_1 = new lv_color_t[this->getDisplayData<LVGL_DisplayData>()->cache];
		break;

	case FLSYSTEM::LVGL8_Driver::CacheMode::TWO_CACHE:

		if (lvgl_displayDriver.buf_1 == nullptr)
			lvgl_displayDriver.buf_1 = new lv_color_t[this->getDisplayData<LVGL_DisplayData>()->cache];

		if (lvgl_displayDriver.buf_2 == nullptr)
			lvgl_displayDriver.buf_2 = new lv_color_t[this->getDisplayData<LVGL_DisplayData>()->cache];
		break;

	default:
		return -1;
		break;
	}

	if (lvgl_displayDriver.disp_buf == nullptr)
		lvgl_displayDriver.disp_buf = new lv_disp_draw_buf_t;
	if (lvgl_displayDriver.disp_drv == nullptr)
		lvgl_displayDriver.disp_drv = new lv_disp_drv_t;

	lv_disp_draw_buf_init(lvgl_displayDriver.disp_buf, lvgl_displayDriver.buf_1, lvgl_displayDriver.buf_2, this->getDisplayData<LVGL_DisplayData>()->cache);
	lv_disp_drv_init(lvgl_displayDriver.disp_drv);
	lvgl_displayDriver.disp_drv->flush_cb = &FLSYSTEM::LVGL8_Driver::_flushFun_;
	lvgl_displayDriver.disp_drv->rounder_cb = &FLSYSTEM::LVGL8_Driver::_rounderFun_;
	lvgl_displayDriver.disp_drv->set_px_cb = &FLSYSTEM::LVGL8_Driver::_set_pxFun_;
	//lvgl_displayDriver.disp_drv->clear_cb = &FLSYSTEM::LVGL8_Driver::_clearFun_;
	lvgl_displayDriver.disp_drv->monitor_cb = &FLSYSTEM::LVGL8_Driver::_monitorFun_;
	lvgl_displayDriver.disp_drv->wait_cb = &FLSYSTEM::LVGL8_Driver::_waitFun_;
	lvgl_displayDriver.disp_drv->clean_dcache_cb = &FLSYSTEM::LVGL8_Driver::_clean_dcacheFun_;
	lvgl_displayDriver.disp_drv->drv_update_cb = &FLSYSTEM::LVGL8_Driver::_drv_updateFun_;
	lvgl_displayDriver.disp_drv->draw_buf = lvgl_displayDriver.disp_buf;
	lvgl_displayDriver.disp_drv->full_refresh = this->getDisplayData<LVGL_DisplayData>()->fullRefresh;
	lvgl_displayDriver.disp_drv->sw_rotate = this->getDisplayData<LVGL_DisplayData>()->swRotate;
	lvgl_displayDriver.disp_drv->hor_res = this->getDisplayData<LVGL_DisplayData>()->screenWidget;
	lvgl_displayDriver.disp_drv->ver_res = this->getDisplayData<LVGL_DisplayData>()->screenHight;
	lvgl_displayDriver.disp_drv->dpi = this->getDisplayData<LVGL_DisplayData>()->dpi;
	lvgl_displayDriver.disp_drv->rotated = this->getDisplayData<LVGL_DisplayData>()->rotated;
	lvgl_displayDriver.disp_drv->antialiasing = this->getDisplayData<LVGL_DisplayData>()->antialiasing;
	lvgl_displayDriver.disp_drv->screen_transp = this->getDisplayData<LVGL_DisplayData>()->screenTransp;
	lvgl_displayDriver.disp_drv->user_data = static_cast<void*>(this);
	lvgl_displayDriver.disp = lv_disp_drv_register(lvgl_displayDriver.disp_drv);

	return 0;
}

void FLSYSTEM::LVGL8_Driver::_flushFun_(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}

	display->flush(disp_drv, area, color_p);
	lv_disp_flush_ready(disp_drv);
}

void FLSYSTEM::LVGL8_Driver::_rounderFun_(struct _lv_disp_drv_t* disp_drv, lv_area_t* area)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->rounder(disp_drv, area);
}

void FLSYSTEM::LVGL8_Driver::_set_pxFun_(struct _lv_disp_drv_t* disp_drv, uint8_t* buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->set_px(disp_drv, buf, buf_w, x, y, color, opa);
}

void FLSYSTEM::LVGL8_Driver::_clearFun_(struct _lv_disp_drv_t* disp_drv, uint8_t* buf, uint32_t size)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->clear(disp_drv, buf, size);
}

void FLSYSTEM::LVGL8_Driver::_monitorFun_(struct _lv_disp_drv_t* disp_drv, uint32_t time, uint32_t px)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->monitor(disp_drv, time, px);
}

void FLSYSTEM::LVGL8_Driver::_waitFun_(struct _lv_disp_drv_t* disp_drv)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->wait(disp_drv);
}

void FLSYSTEM::LVGL8_Driver::_clean_dcacheFun_(struct _lv_disp_drv_t* disp_drv)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->clean_dcache(disp_drv);
}

void FLSYSTEM::LVGL8_Driver::_drv_updateFun_(struct _lv_disp_drv_t* disp_drv)
{
	auto display = static_cast<LVGL8_Driver*>(disp_drv->user_data);
	if (display == nullptr)
	{
		return;
	}
	display->drv_update(disp_drv);
}

void FLSYSTEM::LVGL8_Driver::begin()
{
}

void FLSYSTEM::LVGL8_Driver::loop()
{
#ifndef LV_TICK_CUSTOM
	lv_tick_inc(5);
#endif
	lv_task_handler();
}

#endif