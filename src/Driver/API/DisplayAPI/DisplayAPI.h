#ifndef FLSYSTEM_DISPLAYAPI_H
#define FLSYSTEM_DISPLAYAPI_H

#include "../Driver_API/Driver_API.h"

namespace FLSYSTEM
{
    class DisplayAPI : public Driver_API
    {
    public:
        friend class Display;

        struct DisplayData
        {
            virtual ~DisplayData() {}
            uint16_t screenWidget = 0;
            uint16_t screenHight = 0;
            uint32_t rotated = 2;
            void* userData = nullptr;
        };

    protected:
        explicit DisplayAPI(DisplayData* data = nullptr, FLObject* object = nullptr, const std::string& name = "");
        DisplayAPI(uint16_t screenWidget, uint16_t screenHight, uint32_t rotated = 2, FLObject* object = nullptr, const std::string& name = "");
        virtual DisplayData* createDisplayData() { return new DisplayData(); }

    private:
        DisplayData* displayData = nullptr;

    public:
        virtual ~DisplayAPI();

        template<typename T = DisplayData>
        FLInline T* getDisplayData()
        {
            return static_cast<T*>(displayData);
        }
    };
}

#endif