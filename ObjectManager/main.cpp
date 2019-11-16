

#include "ObjectManager.h"
#include "State.h"
#include "ComposedLog.h"
#include "MemberFuncRegister.h"
#include "Character.h"
#include "ActionController.h"
#include "EventBase.h"
#include "TestEvent.h"

void testObjectManager()
{
	//Logger::instance().redirect("haha.log");
	ObjectManager& inst = CObjectManager::instance();
	std::string id1 = inst.create("state");
	RECORD_LOG("new object[%s]", id1.c_str());
	State* myState = static_cast<State*>(inst.refer(id1));
	myState->modpopulation(1000);
	RECORD_LOG("pop[%d]", myState->getpopulation());
	inst.remove(id1);
}

void testAction()
{
	Logger::instance().redirect("haha.log");
	ObjectManager& inst = CObjectManager::instance();
	std::string id1 = inst.create("state");
	RECORD_LOG("new object[%s]", id1.c_str());
	State* state = static_cast<State*>(inst.refer(id1));
	CActionController::instance().perform(id1, "modpopulation", 100);
	RECORD_LOG("current population[%d]", state->getpopulation());
	CActionController::instance().perform(id1, "modpopulation", 100);
	RECORD_LOG("current population[%d]", state->getpopulation());
	inst.remove(id1);
}

void testEvent()
{
	//Logger::instance().redirect("haha.log");
	TestEvent* test = new TestEvent;
	CEventLoop::instance().addEvent("test_event", 250);
	CEventLoop::instance().exec();
}

int main()
{
	//testRegFunc();
	//testObjectManager();
	//testAction();
	testEvent();
	return 0;
}
