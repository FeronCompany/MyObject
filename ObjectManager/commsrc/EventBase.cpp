

#include "EventBase.h"
#include "ComposedLog.h"

#include <thread>
#include <exception>

EventWheel::~EventWheel()
{
}

void EventWheel::addEvent(EventBase* handler, int64_t delay, int32_t wheelMark)
{
	int32_t wsize = wheel.size();
	int64_t pauseTime = 1000 / wsize;
	int32_t targetMark = (wheelMark + delay / pauseTime) % wsize;
	RECORD_LOG("target mark[%d]", targetMark);
	if (targetMark > wsize)
	{
		RECORD_LOG("wheel oversize[%d][%d]", targetMark, wsize);
		return;
	}
	wheel[targetMark].push_front(handler);
}

void EventWheel::checkMark(int32_t mark)
{
	//RECORD_LOG("current mark[%d]", mark);
	std::list<EventBase*>& curList = wheel[mark];
	for (std::list<EventBase*>::iterator itor = curList.begin(); itor != curList.end(); )
	{
		auto item = *itor;
		if (item->timeout())
		{
			int32_t result = item->process();
			switch (result)
			{
			case EventBase::SINGLE_SHOT:
			{
				delete item;
				break;
			}
			case EventBase::CONSTANT:
			{
				item->setCreateTime(PreciseTime::getNowMiniSec());
				this->addEvent(item, item->getDelay(), mark);
				break;
			}
			default:
				RECORD_LOG("Event Type not right[%d]", result);
				break;
			}

			itor = curList.erase(itor);
		}
		else
		{
			++itor;
		}
	}
}

void EventWheel::resize(int32_t size)
{
	static bool resized = false;
	if (!resized)
	{
		clear();
		wheel.reserve(size);
		for (int count = 0; count < size; count++)
		{
			wheel.push_back(std::list<EventBase*>());
		}
		RECORD_LOG("wheel size[%d]", (int)wheel.size());
		resized = true;
	}
}

void EventWheel::clear()
{
	for (CWheel::iterator itor = wheel.begin(); itor != wheel.end(); ++itor)
	{
		for (std::list<EventBase*>::iterator iter = itor->begin(); iter != itor->end(); ++iter)
		{
			EventBase* pointer = *iter;
			if(pointer) delete pointer;
		}
	}
	CWheel().swap(wheel);
}


/****************** EventLoop *******************/
int EventLoop::exec()
{
	while (true)
	{
		tick();
		pause();
	}
	return 0;
}

void EventLoop::addEvent(const std::string eventName, int64_t delay)
{
	EventBase* handler = CEventFactory::instance().create(eventName);
	if (handler == nullptr)
	{
		RECORD_LOG("NULL POINTER !!!");
		return;
	}
	handler->setDelay(delay);
	eventWheel.addEvent(handler, delay, wheelMark);
}

EventLoop::EventLoop() :
	wheelMark(0)
{
	try
	{
		eventWheel.resize(MAX_TICK);
	}
	catch (std::exception exp)
	{
		RECORD_LOG("ERROR[%s]", exp.what());
	}
}

void EventLoop::tick()
{
	//RECORD_LOG("di da......");
	eventWheel.checkMark(wheelMark);
	wheelMark++;
	if (wheelMark >= MAX_TICK)
	{
		wheelMark = 0;
	}
}

void EventLoop::pause()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE_TIME));
}

EventBase::EventBase()
{
	mCreateTime = PreciseTime::getNowMiniSec();
	mDelay = 0;
}
