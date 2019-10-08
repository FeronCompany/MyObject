

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Template for type registors
*/

#pragma once

#include <string>
#include <map>
#include "CommSingleton.h"


template<class CbFunc, class BaseClass>
class FormatFactory
{
	friend CommSingleton<FormatFactory>;
public:
	BaseClass* create(const std::string& className)
	{
		auto iter = cbFuncMap.find(className);
		if (iter != cbFuncMap.end())
		{
			return (iter->second)();
		}
		else
		{
			return nullptr;
		}
	}

	void join(const std::string& className, CbFunc __cb)
	{
		cbFuncMap.insert(std::make_pair(className, __cb));
	}

private:
	FormatFactory() {}
	FormatFactory(FormatFactory& alFac) {}

	std::map<std::string, CbFunc> cbFuncMap;
};

template<class CbFunc, class BaseClass>
class TypeRegCaller
{
public:
	TypeRegCaller(const std::string& className, CbFunc __cb)
	{
		CommSingleton<FormatFactory<CbFunc, BaseClass>>::instance().join(className, __cb);
	}
};
