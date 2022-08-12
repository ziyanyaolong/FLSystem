#ifndef FLSYSTEM_VIRTUALFILESYSTEMAPI_H
#define FLSYSTEM_VIRTUALFILESYSTEMAPI_H

#define FLSYSTEM_3RD_STRING
#define FLSYSTEM_3RD_STDINT

#include "../../../../PlatformInterface/3rdInclude.h"
#include "../../../../PlatformInterface/FLDefine.h"

namespace FLSYSTEM
{
    class VirtualFileSystemAPI
    {
    public:
        friend class ExternalStorage;

    protected:
        FLInline VirtualFileSystemAPI();

    public:
        FLInline virtual ~VirtualFileSystemAPI();

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