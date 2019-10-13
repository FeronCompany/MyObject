

#pragma once

#include <map>
#include <string>

#include "CommSingleton.h"

class RegFuncManager
{
	friend CommSingleton<RegFuncManager>;
public:
	void addFunc(const std::string& key, void* func);
	void* getFunc(const std::string& key);

private:
	RegFuncManager() {}

private:
	std::map<std::string, void*> mFuncMap;
};

typedef CommSingleton<RegFuncManager> RegfuncManager;

class RegObject
{
public:
	RegObject(const std::string& key, void* func);
};

#define DECLARE_MEMBER_FUNC(class_name, func_name) \
	void func_name(int num); \
	static void st_##func_name(class_name* obj, int num) \
	{ \
		obj->func_name(num);\
	}

#define REG_MEMBER_FUNC(class_name, func_name) \
	RegObject regObj##class_name##func_name(#func_name, (void*)class_name::st_##func_name);
