

#include "StateManager.h"
#include "IdCreator.h"
#include "BaseLogger.h"
#include "MemberFuncRegister.h"

StateManager::~StateManager()
{
	for (auto& item : mObjectTree)
	{
		if (item.second != nullptr)
		{
			delete item.second;
		}
	}
}

std::string StateManager::create(const std::string& name)
{
	BaseObject* object = BaseFactoty::instance().create(name);
	if (object == nullptr)
	{
		COMM_LOG("create object faild");
		return "";
	}
	std::string id = IdUtil::instance().getId(name);
	object->setNo(id);
	mObjectTree[id] = static_cast<State*>(object);

	return id;
}

void StateManager::remove(const std::string& id)
{
	if (id.length() < 8)
	{
		COMM_LOG("id is illegal!");
		return;
	}

	// 去掉id的后七位便是类型type
	std::string type = id.substr(0, id.length() - 7);
	State* object = mObjectTree[id];
	if (object)
	{
		delete object;
		mObjectTree.erase(id);
	}
}

void StateManager::command(const std::string& id, const std::string& command, int value)
{
	State* object = mObjectTree[id];
	if (!object)
	{
		COMM_LOG("object[%s] not exist", id.c_str());
		return;
	}
	
	void* func = RegfuncManager::instance().getFunc(command);
	if (!func)
	{
		COMM_LOG("callback func is null");
		return;
	}
	static_cast<__stateActionFunc>(func)(object, value);
}

void StateManager::refer(const std::string& id, State& value)
{
	State* object = mObjectTree[id];
	if (!object)
	{
		COMM_LOG("object[%s] not exist", id.c_str());
		return;
	}
	value = *object;
}
