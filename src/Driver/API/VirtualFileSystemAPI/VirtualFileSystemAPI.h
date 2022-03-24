#ifndef FLSYSTEM_VIRTUALFILESYSTEMAPI_H
#define FLSYSTEM_VIRTUALFILESYSTEMAPI_H

#include "../Driver_API/Driver_API.h"

namespace FLSYSTEM
{
    class VirtualFileSystemAPI : public Driver_API
    {
    public:
        friend class ExternalStorage;

    protected:
        inline VirtualFileSystemAPI(const char *driver);
        inline VirtualFileSystemAPI(const std::string &driver);

    public:
        inline virtual ~VirtualFileSystemAPI();

        virtual uint8_t open(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t close(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t read(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t seek(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t tell(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t write(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t dirOpen(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t dirRead(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t dirClose(const char *path, uint8_t mode = 0, void *data = nullptr) = 0;
        virtual uint8_t ready(void *drv, uint8_t mode = 0, void *data = nullptr) = 0;
    };
}

#endif