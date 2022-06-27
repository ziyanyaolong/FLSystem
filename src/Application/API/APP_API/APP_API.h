#ifndef FLSYSTEM_APP_API_H
#define FLSYSTEM_APP_API_H

#include "../../../FLSystemConfig.h"

#include <string>
#include <vector>

#include "../../../System/Kernel/API/ProcessScheduleAPI/ProcessScheduleAPI.h"

namespace FLSYSTEM
{
    class APP_API : public ProcessScheduleAPI
    {
    private:
        friend class FLSystem;

    public:
        virtual ~APP_API();

    protected:
        APP_API(FLObject *object = nullptr, const std::string &name = std::string("")) : ProcessScheduleAPI(object, name) {}
        APP_API(const std::string &name) : ProcessScheduleAPI(name) {}

#ifdef FLSYSTEM_ENABLE_LVGL_8
    public:
        virtual void begin(lv_obj_t *obj, lv_event_code_t event) {}
        virtual lv_img_dsc_t *readIcon() { return icon; }
        static void lv_close_event_handler(lv_event_t *e);

    protected:
        virtual void begin() override {}
        virtual void setIcon(const lv_img_dsc_t &Icon);

    private:
        lv_img_dsc_t *icon = nullptr;
#endif
    };
}

#endif