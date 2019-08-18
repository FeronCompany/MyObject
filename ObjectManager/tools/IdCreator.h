

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Create ID
*/

#pragma once
#include <string>
#include <cstdlib>
#include <cstring>

class IdCreator
{
public:
	static IdCreator& instance()
	{
		static IdCreator inst;
		return inst;
	}

	std::string getId(const std::string& type);

private:
	IdCreator();
};
