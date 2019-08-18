

#include "IdCreator.h"

std::string IdCreator::getId(const std::string& type)
{
	if (type.length() > 20)
	{
		return std::string("");
	}
	///TODO...
	static int count = 0;
	count++;
	char buf[30] = { 0 };
	snprintf(buf, sizeof(buf), "%s%07d", type.c_str(), count);
	return buf;
}

IdCreator::IdCreator()
{
	///TODO...
}
