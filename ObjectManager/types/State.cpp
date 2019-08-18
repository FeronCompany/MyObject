

#include "State.h"
#include "../tools/BaseLogger.h"

State::State()
{
	mStateInfo = new StateData;
}

State::State(State&& instance)
{
	if (instance.mStateInfo)
	{
		this->mStateInfo = instance.mStateInfo;
		instance.mStateInfo = nullptr;
	}
	else
	{
		mStateInfo = new StateData;
	}
}

State::~State()
{
	if (mStateInfo)
		delete mStateInfo;
}

void State::init()
{
	Logger::instance().log("State::init()");
}

REG_TYPE(state)
{
	return new State;
}
