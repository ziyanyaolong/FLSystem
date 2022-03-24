#include "APP_API.h"

FLSYSTEM::APP_API::~APP_API()
{
}

#ifdef FLSYSTEM_3RD_LVGL
void FLSYSTEM::APP_API::setIcon(const lv_img_dsc_t &Icon)
{
    if (icon == nullptr)
    {
        icon = new lv_img_dsc_t(Icon);
    }
    else
    {
        *icon = Icon;
    }
}

void FLSYSTEM::APP_API::lv_close_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        if (e->user_data != nullptr)
        {
            lv_obj_del((lv_obj_t *)(e->user_data));
        }
    }
}
#endif