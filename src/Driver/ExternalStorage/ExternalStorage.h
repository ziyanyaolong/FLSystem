#ifndef FLSYSTEM_EXTERNALSTORAGE_H
#define FLSYSTEM_EXTERNALSTORAGE_H

#include "../../System/Kernel/kernel.h"
#include "../API/Driver_API/Driver_API.h"

namespace FLSYSTEM
{
    class ExternalStorage : public Driver_API
    {
    public:
        ExternalStorage(FLObject* parent = nullptr, const std::string& name = std::string(""));
        virtual ~ExternalStorage();
        virtual void begin() override;
        virtual void loop() override;
    };

}

#endif