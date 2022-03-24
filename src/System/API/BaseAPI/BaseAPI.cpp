#include "BaseAPI.h"

std::string FLSYSTEM::BaseAPI::placeholderStr = "";

FLSYSTEM::BaseAPI::BaseAPI()
{

}

FLSYSTEM::BaseAPI::BaseAPI(const std::string &name)
{
    if (name != "")
    {
        m_name = new std::string(name);
    }
}

FLSYSTEM::BaseAPI::~BaseAPI()
{
    if (m_name)
    {
        delete m_name;
        m_name = nullptr;
    }
}
