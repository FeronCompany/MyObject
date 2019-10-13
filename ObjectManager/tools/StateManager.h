

#pragma once

#include "State.h"

class StateManager
{
	friend CommSingleton<StateManager>;
public:
	~StateManager();
	// 返回id
	std::string create(const std::string& name);
	// 按id删除对象
	void remove(const std::string& id);
	// 执行指令
	void command(const std::string& id, const std::string& command, int value);

	void refer(const std::string& id, State& value);

private:
	StateManager() {}
	std::map<std::string, State*> mObjectTree;
};

typedef CommSingleton<StateManager> CStateManager;

typedef void (*__stateActionFunc)(State*, int);
