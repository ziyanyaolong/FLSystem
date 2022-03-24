#include "DisplayAPI.h"

FLSYSTEM::DisplayAPI::~DisplayAPI()
{
}

#ifdef FLSYSTEM_3RD_LVGL
bool FLSYSTEM::DisplayAPI::setDesktopBackground(const lv_img_dsc_t *DBs)
{
    desktopBackground = *DBs;
    if (DBs != nullptr)
    {
        DB = lv_img_create(lv_scr_act());
        lv_img_set_src(DB, &desktopBackground);
        lv_obj_set_size(DB, this->displayData.screenWidget, this->displayData.screenHight);
        lv_obj_set_pos(DB, 0, 0);
        lv_obj_move_background(DB);
        return true;
    }
    else
        return false;
}
#endif