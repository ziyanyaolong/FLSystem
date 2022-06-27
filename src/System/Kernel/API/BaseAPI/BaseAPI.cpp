#include "BaseAPI.h"

std::string FLSYSTEM::BaseAPI::placeholderStr = "";

FLSYSTEM::BaseAPI::BaseAPI()
{
}

FLSYSTEM::BaseAPI::BaseAPI(const std::string& name)
{
	if (!name.empty())
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

FLInline bool FLSYSTEM::BaseAPI::isHaveName()
{
	if (m_name)
	{
		return true;
	}
	else
		return false;
}

FLInline void FLSYSTEM::BaseAPI::setName(const std::string& name)
{
	if (name.empty())
	{
		return;
	}
	else if (!isHaveName())
	{
		m_name = new std::string(name);
	}

	*m_name = name;
}

FLInline void FLSYSTEM::BaseAPI::setName(const char* name)
{
	if (strcmp(name, "") == 0)
	{
		return;
	}
	else if (!isHaveName())
	{
		m_name = new std::string(name);
	}

	*m_name = std::string(name);
}
FLInline const std::string& FLSYSTEM::BaseAPI::readName()
{
	if (!isHaveName())
		return placeholderStr;

	return *m_name;
}