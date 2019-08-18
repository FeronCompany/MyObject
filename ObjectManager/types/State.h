

#pragma once

#include "BaseObject.h"
#include <string>

struct StateData
{
	std::string mID;
	std::string mName;

};

class State : public BaseObject
{
public:
	State();
	State(State&& instance);
	~State();
	void init() override;

private:
	StateData* mStateInfo;
};
