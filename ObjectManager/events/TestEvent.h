

#pragma once

#include "EventBase.h"

class TestEvent : public EventBase
{
public:
	virtual int32_t process() override;
	virtual bool timeout() override;

private:


};
