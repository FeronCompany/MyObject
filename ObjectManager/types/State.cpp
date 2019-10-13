

#include "State.h"
#include "BaseLogger.h"

State::State()
{
	population = 0;
}

State::State(const State& state)
{
	this->population = state.population;
}

State& State::operator=(const State& state)
{
	this->population = state.population;
	return *this;
}

State::~State()
{
}

void State::init()
{
	REG_MEMBER_FUNC_LITE(State, population);
}

void State::modpopulation(int num)
{
	this->population += num;
	if (this->population < 0)
	{
		this->population = 0;
	}
}

REG_TYPE(state)
{
	State* object = SafeNew<State>();
	object->init();
	return object;
}
