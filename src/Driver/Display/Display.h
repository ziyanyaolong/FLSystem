#ifndef FLSYSTEM_DISPLAY_H
#define FLSYSTEM_DISPLAY_H

#include "../../PlatformInterface/PlatformInterface.h"
#include "../../System/Kernel/Arch/SafeSTL/FLVector/FLVector.h"
#include "../../System/Kernel/kernel.h"
#include "../API/DisplayAPI/DisplayAPI.h"
#include "../../System/Components/Registry/Registry.h"

namespace FLSYSTEM
{
    class Display : public Driver_API
    {
    private:
        Registry<DisplayAPI*> displayList;

    public:
        Display(FLObject* parent = nullptr, const std::string &name = std::string("")) : Driver_API(parent, name) {}

        virtual ~Display();

    public:
        virtual void begin() override
        {
            
        }

        virtual void loop() override;

        FLInline bool registerDisplay(DisplayAPI* api);
    };
}

#endif