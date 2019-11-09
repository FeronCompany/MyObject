

#pragma once

#include "CommSingleton.h"

#include <string>
#include <vector>
#include <list>

class EventBase
{
public:
	virtual ~EventBase() {}
	virtual void process() = 0;
	virtual bool timeout() = 0;
};

class EventWheel
{
	typedef std::vector<std::list<EventBase*>> CWheel;
public:
	EventWheel() {}
	~EventWheel();

	void addEvent(EventBase* handler, int32_t mark);
	void remove(EventBase* handler);
	void checkMark(int32_t mark);
	void resize(int32_t size);
	void clear();

private:
	CWheel wheel;

};

class EventLoop
{
	friend CommSingleton<EventLoop>;
public:
	~EventLoop() {}

	int exec();
	void addEvent(EventBase* handler, int32_t delay);

private:
	EventLoop();
	void init();
	void tick();
	void pause();

private:
	EventWheel eventWheel;
	int32_t wheelMark;

	const int32_t PAUSE_TIME = 20;
	const int32_t MAX_TICK = 50;
};

typedef CommSingleton<EventLoop> CEventLoop;
