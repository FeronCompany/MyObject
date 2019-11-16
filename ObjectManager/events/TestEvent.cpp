

#include "TestEvent.h"
#include "ComposedLog.h"

int32_t TestEvent::process()
{
	RECORD_LOG("TestEvent!!!");
	return CONSTANT;
}

bool TestEvent::timeout()
{
	return PreciseTime::getNowMiniSec() >= getCreateTime() + getDelay();
}

REG_TYPE(TestEvent, test_event);
