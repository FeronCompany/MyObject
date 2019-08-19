

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

void State::setNo(const std::string& no)
{
	mStateInfo->mID = no;
}

REG_TYPE(state)
{
	State* object = new State;
	object->init();
	return object;
}
