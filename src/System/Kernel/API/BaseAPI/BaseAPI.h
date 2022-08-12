#ifndef FLSYSTEM_BASEAPI_H
#define FLSYSTEM_BASEAPI_H

#define FLSYSTEM_3RD_STRING
#define FLSYSTEM_3RD_STRINGTOC

#include "../../../../PlatformInterface/3rdInclude.h"
#include "../../../../PlatformInterface/FLDefine.h"
#include "../GC_API/GC_API.h"

namespace FLSYSTEM
{
    class BaseAPI : public GC_API
    {
    private:
        static std::string placeholderStr;
        std::string *m_name = nullptr;

        bool isHaveName();

    protected:
        BaseAPI();
        BaseAPI(const std::string &name);

    public:
        virtual ~BaseAPI();

        void setName(const std::string& name);
        void setName(const char* name);

        const std::string& readName();
    };
}

#endif