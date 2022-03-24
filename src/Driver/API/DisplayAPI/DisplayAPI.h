#ifndef FLSYSTEM_DISPLAYAPI_H
#define FLSYSTEM_DISPLAYAPI_H

#include "../Driver_API/Driver_API.h"

namespace FLSYSTEM
{
    class DisplayAPI : public Driver_API
    {
    public:
        friend class Display;
        enum class CacheMode
        {
            ONE_CACHE = 0X0,
            TWO_CACHE = 0X1
        };
        struct DisplayData
        {
            uint16_t screenWidget = 0;
            uint16_t screenHight = 0;
            void *userData = nullptr;
#ifdef FLSYSTEM_3RD_LVGL
            uint32_t fullRefresh = 1;
            uint8_t swRotate = 1;
            uint32_t antialiasing = 1;
            uint32_t rotated = 2;
            uint32_t screenTransp = 1;
            uint32_t dpi = 10;
            uint64_t cache = (screenWidget * screenHight) / 10;
            FLSYSTEM::DisplayAPI::CacheMode cacheMode = FLSYSTEM::DisplayAPI::CacheMode::ONE_CACHE;
#endif
        };

#ifdef FLSYSTEM_3RD_LVGL
        struct DisplayDriver
        {
            lv_disp_draw_buf_t *disp_buf = nullptr;
            lv_disp_drv_t *disp_drv = nullptr;
            lv_disp_t *disp = nullptr;
            lv_color_t *buf_1 = nullptr;
            lv_color_t *buf_2 = nullptr;
        };

        bool setDesktopBackground(const lv_img_dsc_t *DBs);
#else
            typedef void (*displayDrawFun)();
            displayDrawFun drawFun = nullptr;
#endif

    protected:
        DisplayData displayData;
#ifdef FLSYSTEM_3RD_LVGL
        DisplayDriver displayDriver;
#endif
        DisplayAPI(const std::string &name) : Driver_API(name) {}

    public:
        virtual ~DisplayAPI();

        DisplayData &getDisplayData()
        {
            return displayData;
        }

#ifdef FLSYSTEM_3RD_LVGL
        DisplayDriver &getDisplayDriver()
        {
            return displayDriver;
        }
        virtual void flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) = 0;

    private:
        static void _runFunFlush_(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
        {
            auto display = static_cast<DisplayAPI *>(disp_drv->user_data);
            if (display == nullptr)
            {
                FLTaskDelay(1);
                return;
            }

            display->flush(disp_drv, area, color_p);
            lv_disp_flush_ready(disp_drv);
        }
        lv_img_dsc_t desktopBackground = lv_img_dsc_t();
        lv_obj_t *DB = nullptr;
#endif
    };
}

#endif