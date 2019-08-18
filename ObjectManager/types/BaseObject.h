

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Protocol type
*/

#pragma once

#include "../tools/TypeRegSingleton.h"

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}
	virtual void init() = 0;
};

typedef BaseObject* (*__objectGetter)();
typedef FormatFactory<__objectGetter, BaseObject> BaseFactoty;
typedef TypeRegCaller<__objectGetter, BaseObject> BaseRegCaller;

#define REG_TYPE(__cb_func) \
BaseObject* __cb_func(); \
BaseRegCaller caller##__cb_func(#__cb_func, __cb_func); \
BaseObject* __cb_func()
