

#include "MemberFuncRegister.h"

void RegFuncManager::addFunc(const std::string& key, void* func)
{
	mFuncMap[key] = func;
}

void* RegFuncManager::getFunc(const std::string& key)
{
	auto iter = mFuncMap.find(key);
	if (iter != mFuncMap.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

RegObject::RegObject(const std::string& key, void* func)
{
	RegfuncManager::instance().addFunc(key, func);
}
