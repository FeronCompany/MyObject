

#include "ObjectManager.h"
#include "StateManager.h"
#include "BaseLogger.h"
#include "MemberFuncRegister.h"
#include "CrudePointer.h"
#include "Character.h"

void testObjectManager()
{
	Logger::instance().redirect("haha.log");
	ObjectManager& inst = CObjectManager::instance();
	std::string id1 = inst.create("state");
	COMM_LOG("new object[%s]", id1.c_str());
	State* myState = static_cast<State*>(inst.refer(id1));
	myState->modpopulation(1000);
	COMM_LOG("pop[%d]", myState->getpopulation());
	inst.remove(id1);
}

void testStateManager()
{
	Logger::instance().redirect("haha.log");
	StateManager& inst = CStateManager::instance();
	std::string id1 = inst.create("state");
	COMM_LOG("new object[%s]", id1.c_str());

	State state;
	inst.refer(id1, state);
	COMM_LOG("state population[%d]", state.getpopulation());

	inst.command(id1, "modpopulation", 1500);
	inst.refer(id1, state);
	COMM_LOG("state population[%d]", state.getpopulation());

	inst.command(id1, "modpopulation", -1200);
	inst.refer(id1, state);
	COMM_LOG("state population[%d]", state.getpopulation());

	inst.command(id1, "modpopulation", -1200);
	inst.refer(id1, state);
	COMM_LOG("state population[%d]", state.getpopulation());

	inst.remove(id1);
}

void testCrudePointer()
{
	/*State* myState = new State;
	CrudePointer<State> state(myState);
	(*state).init();
	COMM_LOG("%d", (*state).getpopulation());
	delete myState;*/
	CrudePointer<Character> state(NULL);
}

int main()
{
	//testRegFunc();
	testObjectManager();
	//testStateManager();
	//testCrudePointer();
	return 0;
}
