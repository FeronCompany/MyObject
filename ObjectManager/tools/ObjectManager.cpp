

#include "ObjectManager.h"
#include "../tools/IdCreator.h"
#include "BaseLogger.h"

ObjectManager::~ObjectManager()
{
	for (auto& flItem : mObjectTree)
	{
		for (auto& secItem : flItem.second)
		{
			if (secItem.second)
			{
				delete secItem.second;
			}
		}
	}
}

std::string ObjectManager::create(const std::string& name)
{
	BaseObject* object = CObjectFactoty::instance().create(name);
	if (object == nullptr)
	{
		Logger::instance().log("create object faild");
		return "";
	}
	std::string id = IdUtil::instance().getId(name);
	object->setNo(id);
	mObjectTree[name][id] = object;

	return id;
}

void ObjectManager::remove(const std::string& id)
{
	if (!checkNo(id))
	{
		return;
	}
	// 去掉id的后七位便是类型type
	std::string type = id.substr(0, id.length() - 7);
	BaseObject* object = mObjectTree[type][id];
	if (object)
	{
		delete object;
		mObjectTree[type].erase(id);
	}
	
}

BaseObject* ObjectManager::refer(const std::string& id)
{
	if (!checkNo(id))
	{
		return nullptr;
	}
	std::string type = id.substr(0, id.length() - 7);
	BaseObject* object = mObjectTree[type][id];
	return object;
}

bool ObjectManager::checkNo(const std::string& id)
{
	if (id.length() < 8)
	{
		Logger::instance().log("id is illegal!");
		return false;
	}

	return true;
}
