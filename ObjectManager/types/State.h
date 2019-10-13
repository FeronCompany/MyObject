

#pragma once

#include "BaseObject.h"
#include "MemberFuncRegister.h"

class State : public BaseObject
{
public:
	State();
	State(const State& state);
	~State();
	State& operator=(const State& state);
	void init() override;

	// getters and setters
	DECLARE_MOD_AND_GET(State, population, int32_t);

private:
	int32_t population;
};
