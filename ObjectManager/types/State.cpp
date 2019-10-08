

#include "State.h"
#include "BaseLogger.h"

State::State()
{
	mStateInfo = SafeNew<StateData>();
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
		mStateInfo = SafeNew<StateData>();
	}
}

State::~State()
{
	if (mStateInfo)
		delete mStateInfo;
}

void State::init()
{
	COMM_LOG("state");;
}

void State::setNo(const std::string& no)
{
	mStateInfo->mID = no;
}

REG_TYPE(state)
{
	State* object = SafeNew<State>();
	object->init();
	return object;
}
