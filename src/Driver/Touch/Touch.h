#ifndef FLSYSTEM_TOUCH_H
#define FLSYSTEM_TOUCH_H

#define FLSYSTEM_3RD_STRING

#include "../../PlatformInterface/PlatformInterface.h"

namespace FLSYSTEM
{
    class Touch
    {
    private:
#ifdef FLSYSTEM_3RD_LVGL
        lv_indev_t *touchIndev;
        lv_indev_drv_t touchIndevDrv;
#endif

    public:
        Touch();
        virtual ~Touch();

        enum Mode
        {
            SPI,
            Parallel
        };
        
        // static void TouchInputRead(lv_indev_drv_t *drv, lv_indev_data_t *data);
        // bool installTouch();
    };
}

#endif
