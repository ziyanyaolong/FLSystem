#ifndef FLSYSTEM_BASEAPI_H
#define FLSYSTEM_BASEAPI_H

#define FLSYSTEM_3RD_STRING

#include "../../../PlatformInterface/PlatformInterface.h"

namespace FLSYSTEM
{
    class BaseAPI
    {
    private:
        static std::string placeholderStr;
        std::string *m_name = nullptr;

        bool isHaveName()
        {
            if (m_name)
            {
                return true;
            }
            else
                return false;
        }

    protected:
        BaseAPI();
        BaseAPI(const std::string &name);

    public:
        virtual ~BaseAPI();

        void setName(const std::string &name)
        {
            if (name == "")
                return;
                
            if (!isHaveName())
                m_name = new std::string(name);
            
            *m_name = name;
        }

        void setName(const char *name)
        {
            if (name == "")
                return;

            if (!isHaveName())
                m_name = new std::string(name);

            *m_name = std::string(name);
        }
        const std::string& readName()
        {
            if (!isHaveName())
                return placeholderStr;

            return *m_name;
        }
    };
}

#endif