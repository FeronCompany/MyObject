

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Template for type registors
*/

#pragma once

#include <string>
#include <map>
#include "CommSingleton.h"

class TypeRegContainer
{
	friend CommSingleton<TypeRegContainer>;
public:
	void* create(const std::string& className)
	{
		auto iter = cbFuncMap.find(className);
		if (iter != cbFuncMap.end())
		{
			return iter->second;
		}
		else
		{
			return nullptr;
		}
	}

	void join(const std::string& className, void* __cb)
	{
		cbFuncMap.insert(std::make_pair(className, __cb));
	}

private:
	TypeRegContainer() {}
	TypeRegContainer(TypeRegContainer& alFac) {}

	std::map<std::string, void*> cbFuncMap;
};
typedef CommSingleton<TypeRegContainer> CTypeRegContainer;

template<class BaseClass>
class TypeFactory
{
	typedef BaseClass* (*CbFunc)();
	friend CommSingleton<TypeFactory>;
public:
	BaseClass* create(const std::string& className)
	{
		void* funcPtr = CTypeRegContainer::instance().create(className);
		if (funcPtr == nullptr)
		{
			return nullptr;
		}
		return static_cast<CbFunc>(funcPtr)();
	}

	void join(const std::string& className, CbFunc __cb)
	{
		CTypeRegContainer::instance().join(className, static_cast<void*>(__cb));
	}

private:
	TypeFactory() {}
	TypeFactory(TypeFactory& alFac) {}
};

template <typename T>
T* SafeNew()
{
	T* ptr = nullptr;
	try
	{
		ptr = new T;
	}
	catch (...)
	{
		///Do nothing for now ...
	}
	return ptr;
}

template<class BaseClass>
class TypeRegCaller
{
public:
	TypeRegCaller(const std::string& className)
	{
		CommSingleton<TypeFactory<BaseClass>>::instance().join(className, getInstance);
	}

	static BaseClass* getInstance()
	{
		return SafeNew<BaseClass>();
	}
};

#define REG_TYPE(TypeName, __cb_func) TypeRegCaller<TypeName> caller##__cb_func(#__cb_func)
