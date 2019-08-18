

/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Object manager
*/

#pragma once

#include "BaseObject.h"
#include <map>

class ObjectManager
{
public:
	~ObjectManager();
	static ObjectManager& instance();
	// ����id
	std::string create(const std::string& name);
	// ��idɾ������
	void remove(const std::string& id);

private:
	ObjectManager() {}
	std::map<std::string, std::map<std::string, BaseObject*>> mObjectTree;
};
