

#pragma once

#include "BaseObject.h"

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
	void setNo(const std::string& no) override;

private:
	StateData* mStateInfo;
};
