

#pragma once

#include "TypeRegSingleton.h"
#include "MyTime.h"

#include <string>
#include <vector>
#include <list>

class EventBase
{
public:
	enum ReturnType
	{
		SINGLE_SHOT = 0,
		CONSTANT = 1,
	};

public:
	virtual ~EventBase() {}
	virtual int32_t process() = 0; // return 0 if singleshot, return 1 if loop
	virtual bool timeout() = 0;
	
	EventBase();
	/*{
		
	}*/
	int64_t getDelay()
	{
		return mDelay;
	}
	void setDelay(int64_t delay)
	{
		mDelay = delay;
	}
	void setCreateTime(int64_t bTime)
	{
		mCreateTime = bTime;
	}
	int64_t getCreateTime()
	{
		return mCreateTime;
	}
private:
	int64_t	mDelay;
	int64_t mCreateTime;
};

class EventWheel
{
	typedef std::vector<std::list<EventBase*>> CWheel;
public:
	EventWheel() {}
	~EventWheel();

	void addEvent(EventBase* handler, int64_t delay, int32_t wheelMark);
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
	void addEvent(const std::string eventName, int64_t delay);

private:
	EventLoop();
	void tick();
	void pause();

private:
	EventWheel eventWheel;
	int32_t wheelMark;

	static const int32_t PAUSE_TIME = 20;
	static const int32_t MAX_TICK = 50;
};

typedef CommSingleton<EventLoop> CEventLoop;
typedef CommSingleton<TypeFactory<EventBase>> CEventFactory;
