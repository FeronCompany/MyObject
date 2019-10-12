

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

map<string, void*> aaMap;

class RegObject
{
public:
	RegObject(const string& key, void* func)
	{
		aaMap[key] = func;
	}
};

#define DECLARE_MEMBER_FUNC(class_name, func_name) \
	void func_name(int num); \
	static void st_##func_name(class_name* obj, int num) \
	{ \
		obj->func_name(num);\
	}

#define REG_MEMBER_FUNC(class_name, func_name) \
	RegObject regObj##class_name##func_name(#func_name, (void*)class_name::st_##func_name);

class TestRegFunc
{
public:
	TestRegFunc() :health(0) {}
	DECLARE_MEMBER_FUNC(TestRegFunc, healthMod);

	void tell()
	{
		cout << "health[" << health << "]\n";
	}

private:
	int32_t health;
};

void TestRegFunc::healthMod(int num)
{
	this->health += num;
}

REG_MEMBER_FUNC(TestRegFunc, healthMod);

typedef void (*member_func)(TestRegFunc*, int);

void testRegFunc()
{
	TestRegFunc aaa;
	aaa.tell();
	void* func = aaMap["healthMod"];
	static_cast<member_func>(func)(&aaa, 5);
	aaa.tell();
}

