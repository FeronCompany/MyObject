

#include "IdCreator.h"

std::string IdCreator::getId(const std::string& type)
{
	if (type.length() > 20)
	{
		return std::string("");
	}

	int32_t count = 1;
	auto iter = mSerialNoMap.find(type);
	if (iter == mSerialNoMap.end())
	{
		mSerialNoMap.insert(std::make_pair(type, count));
	}
	else
	{
		count = iter->second + 1;
	}
	char buf[30] = { 0 };
	snprintf(buf, sizeof(buf), "%s%07d", type.c_str(), count);
	return buf;
}

IdCreator::IdCreator()
{
	///TODO...
}
