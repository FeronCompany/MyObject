

#include "Configure.h"

void Configure_T::add(const std::string& key, const std::string& value)
{
	mConfigMap[key] = value;
}

std::string Configure_T::getStrConfig(const std::string& key)
{
	return mConfigMap[key];
}

int32_t Configure_T::getIntConfig(const std::string& key)
{
	return std::stoi(mConfigMap[key]);
}

double Configure_T::getDoubleConfig(const std::string& key)
{
	return std::stod(mConfigMap[key]);
}

void Configure_T::clear()
{
	std::map<std::string, std::string>().swap(mConfigMap);
}
