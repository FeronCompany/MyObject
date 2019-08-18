

#include "ObjectManager.h"
#include "../tools/IdCreator.h"
#include "../tools/BaseLogger.h"

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

ObjectManager& ObjectManager::instance()
{
	static ObjectManager inst;
	return inst;
}

std::string ObjectManager::create(const std::string& name)
{
	BaseObject* object = BaseFactoty::instance().create(name);
	if (object == nullptr)
	{
		Logger::instance().log("create object faild");
		return "";
	}
	std::string id = IdCreator::instance().getId(name);
	mObjectTree[name][id] = object;

	return id;
}

void ObjectManager::remove(const std::string& id)
{
	if (id.length() < 8)
	{
		Logger::instance().log("id is illegal!");
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
