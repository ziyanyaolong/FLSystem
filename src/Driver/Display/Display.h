#ifndef FLSYSTEM_DISPLAY_H
#define FLSYSTEM_DISPLAY_H

#include "../../PlatformInterface/PlatformInterface.h"
#include "../../System/SafeSTL/FLVector/FLVector.h"
#include "../../System/Kernel/kernel.h"
#include "../API/DisplayAPI/DisplayAPI.h"

namespace FLSYSTEM
{
    class Display : public Driver_API
    {
    public:
        Display(const std::string &name) : Driver_API(name) {}
        Display(const char *name) : Driver_API(name) {}

        virtual ~Display();

    public:
        virtual void begin() override
        {
        }

        virtual void loop() override;
    };
}

#endif