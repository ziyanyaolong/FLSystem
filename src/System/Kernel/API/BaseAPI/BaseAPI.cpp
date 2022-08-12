#include "BaseAPI.h"

std::string FLSYSTEM::BaseAPI::placeholderStr = "";

FLSYSTEM::BaseAPI::BaseAPI() : GC_API()
{
}

FLSYSTEM::BaseAPI::BaseAPI(const std::string& name) : GC_API()
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

bool FLSYSTEM::BaseAPI::isHaveName()
{
	if (m_name)
	{
		return true;
	}
	else
		return false;
}

void FLSYSTEM::BaseAPI::setName(const std::string& name)
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

void FLSYSTEM::BaseAPI::setName(const char* name)
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

const std::string& FLSYSTEM::BaseAPI::readName()
{
	if (!isHaveName())
		return placeholderStr;

	return *m_name;
}