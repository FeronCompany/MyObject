

/*
* Author	FeronCompany
* Date		2019-08-19
* Function	Template for all singleton
*/

#pragma once

template<typename T>
class CommSingleton
{
public:
	static T& instance()
	{
		static T inst;
		return inst;
	}

private:
	CommSingleton() {}
	CommSingleton(CommSingleton& comm) {}
};
