#ifndef FLSYSTEM_EXTERNALSTORAGE_H
#define FLSYSTEM_EXTERNALSTORAGE_H

#include "../../System/Kernel/kernel.h"
#include "../API/VirtualFileSystemAPI/VirtualFileSystemAPI.h"

namespace FLSYSTEM
{
    class ExternalStorage : public Driver_API
    {
    public:
        ExternalStorage(const std::string &str);
        ExternalStorage(const char *str);
        virtual ~ExternalStorage();
        virtual void begin() override;
        virtual void loop() override;
    };

}

#endif