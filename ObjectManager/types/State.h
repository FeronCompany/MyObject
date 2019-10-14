

#pragma once

#include "BaseObject.h"
#include "MemberFuncRegister.h"
#include "Trait.h"

class State : public BaseObject
{
public:
	State();
	State(const State& state);
	~State();
	State& operator=(const State& state);
	void init() override;
	void addTrait(const std::string& traitName);
	std::string showTrait(const std::string& traitName);
	void calcuAttr();

	// getters and setters
	DECLARE_MOD_AND_GET(State, population, int32_t);

private:
	int32_t population;
	std::vector<Trait*> mTraitList;
};

typedef void (*__stateActionFunc)(State*, int);
