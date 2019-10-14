

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
	friend CommSingleton<ObjectManager>;
public:
	~ObjectManager();
	// ����id
	std::string create(const std::string& name);
	// ��idɾ������
	void remove(const std::string& id);
	// ���ض����ָ��
	BaseObject* refer(const std::string& id);

private:
	bool checkNo(const std::string& id);
	ObjectManager() {}
	std::map<std::string, std::map<std::string, BaseObject*>> mObjectTree;
};

typedef CommSingleton<ObjectManager> CObjectManager;
