

#include "EventBase.h"
#include "ComposedLog.h"

#include <chrono>
#include <thread>

EventWheel::~EventWheel()
{
}

void EventWheel::addEvent(EventBase* handler, int32_t mark)
{
	int wsize = wheel.size();
	if (mark > wsize)
	{
		RECORD_LOG("wheel oversize[%d][%d]", mark, wsize);
		return;
	}
	wheel[mark].push_front(handler);
}

void EventWheel::checkMark(int32_t mark)
{
	//RECORD_LOG("current mark[%d]", mark);
	std::list<EventBase*>& curList = wheel[mark];
	for (std::list<EventBase*>::iterator itor = curList.begin(); itor != curList.end(); ++itor)
	{
		auto item = *itor;
		if (item->timeout())
		{
			item->process();
			delete item;
			itor = curList.erase(itor);
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
	init();
	while (true)
	{
		tick();
		pause();
	}
	return 0;
}

void EventLoop::addEvent(EventBase* handler, int32_t delay)
{
	if (handler == nullptr)
	{
		RECORD_LOG("NULL POINTER !!!");
		return;
	}
	eventWheel.addEvent(handler, delay);
}

EventLoop::EventLoop() :
	wheelMark(0)
{
}

void EventLoop::init()
{
	eventWheel.resize(MAX_TICK);
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
