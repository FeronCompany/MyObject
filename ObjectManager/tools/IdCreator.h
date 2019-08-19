

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Create ID
*/

#pragma once
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>
#include "CommSingleton.h"

class IdCreator
{
	friend CommSingleton<IdCreator>;
public:
	std::string getId(const std::string& type);

private:
	IdCreator();

private:
	std::map<std::string, int32_t> mSerialNoMap;
};

typedef CommSingleton<IdCreator> IdUtil;
