

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Protocol type
*/

#pragma once

#include <string>
#include "TypeRegSingleton.h"

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}
	virtual void init() = 0;
	virtual void setNo(const std::string& serialNo) = 0;
};

typedef BaseObject* (*__objectGetter)();
typedef CommSingleton<FormatFactory<__objectGetter, BaseObject>> BaseFactoty;
typedef TypeRegCaller<__objectGetter, BaseObject> BaseRegCaller;

#define REG_TYPE(__cb_func) \
BaseObject* __cb_func(); \
BaseRegCaller caller##__cb_func(#__cb_func, __cb_func); \
BaseObject* __cb_func()

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
