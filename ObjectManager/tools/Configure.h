

#pragma once

#include <map>
#include <string>

class Configure_T
{
public:
	void add(const std::string& key, const std::string& value);

	std::string getStrConfig(const std::string& key);
	int32_t getIntConfig(const std::string& key);
	double getDoubleConfig(const std::string& key);

	void clear();

private:
	std::map<std::string, std::string> mConfigMap;
};

