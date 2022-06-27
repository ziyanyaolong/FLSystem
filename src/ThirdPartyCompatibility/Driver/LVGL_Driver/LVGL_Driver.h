#ifndef FLSYSTEM_LVGL_DRIVER_H
#define FLSYSTEM_LVGL_DRIVER_H

#include "../../../PlatformInterface/PlatformInterface.h"

#ifdef FLSYSTEM_ENABLE_LVGL

#include "../../../Driver/API/DisplayAPI/DisplayAPI.h"

#define FLSYSTEM_3RD_LVGL

#include "../../../PlatformInterface/3rdInclude.h"

namespace FLSYSTEM
{
	class LVGL_Driver : public DisplayAPI
	{
	public:
		explicit LVGL_Driver(DisplayData* data = nullptr, FLObject* object = nullptr, const std::string& name = "") : DisplayAPI(data, object, name) {}
		LVGL_Driver(uint16_t screenWidget, uint16_t screenHight, uint32_t rotated = 2, FLObject* object = nullptr, const std::string& name = "") : DisplayAPI(screenWidget, screenHight, rotated, object ,name) {}
		virtual ~LVGL_Driver() {}

		enum class CacheMode
		{
			ONE_CACHE = 0X0,
			TWO_CACHE = 0X1
		};

		struct LVGL_DisplayData : public DisplayAPI::DisplayData
		{
			uint32_t fullRefresh = 1;
			uint8_t swRotate = 1;
			uint32_t antialiasing = 1;
			uint32_t screenTransp = 1;
			uint32_t dpi = 10;
			uint32_t cache = (screenWidget * screenHight) / 10;
			FLSYSTEM::LVGL_Driver::CacheMode cacheMode = FLSYSTEM::LVGL_Driver::CacheMode::ONE_CACHE;
		};

		struct LVGL_DisplayDriver
		{
			lv_disp_draw_buf_t* disp_buf = nullptr;
			lv_disp_drv_t* disp_drv = nullptr;
			lv_disp_t* disp = nullptr;
			lv_color_t* buf_1 = nullptr;
			lv_color_t* buf_2 = nullptr;
		};

		virtual void flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p) {}
		virtual void rounder(struct _lv_disp_drv_t* disp_drv, lv_area_t* area) {}
		virtual void set_px(struct _lv_disp_drv_t* disp_drv, uint8_t* buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y,
			lv_color_t color, lv_opa_t opa) {}
		virtual void clear(struct _lv_disp_drv_t* disp_drv, uint8_t* buf, uint32_t size) {}
		virtual void monitor(struct _lv_disp_drv_t* disp_drv, uint32_t time, uint32_t px) {}
		virtual void wait(struct _lv_disp_drv_t* disp_drv) {}
		virtual void clean_dcache(struct _lv_disp_drv_t* disp_drv) {}
		virtual void drv_update(struct _lv_disp_drv_t* disp_drv) {}

		bool setDesktopBackground(const lv_img_dsc_t* DBs);

	protected:
		virtual DisplayData* createDisplayData() override { return static_cast<DisplayAPI::DisplayData*>(new LVGL_DisplayData()); }
		virtual int regIn() override;

	private:
		LVGL_DisplayDriver lvgl_displayDriver;

		static void _flushFun_(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p);
		static void _rounderFun_(struct _lv_disp_drv_t* disp_drv, lv_area_t* area);
		static void _set_pxFun_(struct _lv_disp_drv_t* disp_drv, uint8_t* buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
		static void _clearFun_(struct _lv_disp_drv_t* disp_drv, uint8_t* buf, uint32_t size);
		static void _monitorFun_(struct _lv_disp_drv_t* disp_drv, uint32_t time, uint32_t px);
		static void _waitFun_(struct _lv_disp_drv_t* disp_drv);
		static void _clean_dcacheFun_(struct _lv_disp_drv_t* disp_drv);
		static void _drv_updateFun_(struct _lv_disp_drv_t* disp_drv);

		lv_img_dsc_t desktopBackground = lv_img_dsc_t();
		lv_obj_t* DB = nullptr;
	};
}

#endif

#endif
