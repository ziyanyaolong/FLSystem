#ifndef FLSYSTEM_DRIVER_API_H
#define FLSYSTEM_DRIVER_API_H

#include "../../../System/API/ProcessScheduleAPI/ProcessScheduleAPI.h"

namespace FLSYSTEM
{
    class Driver_API : public ProcessScheduleAPI
    {
    private:
        friend class FLSystem;
        
    protected:
        Driver_API(FLObject *object = nullptr, const std::string &name = std::string("")) : ProcessScheduleAPI(object, name) {}
        Driver_API(const std::string &name) : ProcessScheduleAPI(name) {}

    public:
        virtual ~Driver_API() {}
    };
}

#endif