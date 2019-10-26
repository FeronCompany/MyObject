

#include "ObjectManager.h"
#include "State.h"
#include "ComposedLog.h"
#include "MemberFuncRegister.h"
#include "CrudePointer.h"
#include "Character.h"

void testObjectManager()
{
	Logger::instance().redirect("haha.log");
	ObjectManager& inst = CObjectManager::instance();
	std::string id1 = inst.create("state");
	RECORD_LOG("new object[%s]", id1.c_str());
	State* myState = static_cast<State*>(inst.refer(id1));
	myState->modpopulation(1000);
	RECORD_LOG("pop[%d]", myState->getpopulation());
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
	//testCrudePointer();
	return 0;
}
