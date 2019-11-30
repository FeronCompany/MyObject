

#include "ObjectManager.h"
#include "State.h"
#include "ComposedLog.h"
#include "MemberFuncRegister.h"
#include "Character.h"
#include "ActionController.h"
#include "EventBase.h"
#include "TestEvent.h"
#include "ArgumentParser.h"
#include "PathFinder.h"

#include <exception>

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
	CEventLoop::instance().addEvent("test_event", 250);
	CEventLoop::instance().exec();
}

void testArgument(int argc, char** argv)
{
	ArgumentParser parser;
	try
	{
		COption options[] = {
			{"help", 'h', EN_ARG_TYPE_NO_ARG, "find help infomation", "follow no extra info"},
			{"overwhelm", 'o', EN_ARG_TYPE_REQUIRE_ARG, "add extra attack to your actor", "follow with the attack value you want add"}
		};
		parser.addDefaultArgs(options, sizeof(options) / sizeof(options[0]));
		parser.parse(argc, argv);
	}
	catch (std::exception& exp)
	{
		RECORD_LOG("%s", exp.what());
	}
}

void testPathFinder()
{
	PathFinder pathFinder;
	pathFinder.setMapSize(10, 10);
	TwoDArray<PositionNode>& myMap = pathFinder.getMap();
	myMap(2, 2).access = 0;
	myMap(2, 3).access = 0;
	myMap(2, 4).access = 0;
	myMap(2, 5).access = 0;
	myMap(2, 6).access = 0;
	myMap(2, 7).access = 0;
	myMap(3, 4).access = 0;
	myMap(4, 4).access = 0;
	myMap(5, 4).access = 0;
	myMap(6, 4).access = 0;
	myMap(5, 1).access = 0;
	myMap(5, 2).access = 0;
	myMap(5, 3).access = 0;
	myMap(6, 5).access = 0;
	myMap(7, 5).access = 0;
	myMap(8, 5).access = 0;
	myMap(6, 6).access = 0;
	myMap(6, 7).access = 0;
	myMap(5, 7).access = 0;

	pathFinder.setStartPos(1, 1);
	pathFinder.setTargetPos(5, 5);
	std::vector<PositionNode> nodeMap;
	pathFinder.getPath(nodeMap);
	for (auto& node : nodeMap)
	{
		PURE_LOG("%d, %d", node.pos.x, node.pos.y);
	}
}
/*
1 1 1 1 1 1 1 1 1 1
1 6 1 1 1 0 1 1 1 1
1 1 0 1 1 0 1 1 1 1
1 1 0 1 1 0 1 1 1 1
1 1 0 0 0 0 0 1 1 1
1 1 0 1 1 6 0 0 0 1
1 1 0 1 1 1 0 1 1 1
1 1 0 1 1 0 0 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
*/
int main(int argc, char** argv)
{
	//testRegFunc();
	//testObjectManager();
	//testAction();
	//testEvent();
	//testArgument(argc, argv);
	testPathFinder();
	return 0;
}
