

#include "ObjectManager.h"
#include "StateManager.h"
#include "BaseLogger.h"
#include "MemberFuncRegister.h"

class TestRegFunc
{
public:
	TestRegFunc() :health(0) {}
	DECLARE_MOD_AND_GET(TestRegFunc, health, int32_t);

	void init()
	{
		REG_MEMBER_FUNC_LITE(TestRegFunc, health);
	}

private:
	int32_t health;
};

void TestRegFunc::modhealth(int num)
{
	this->health += num;
}

typedef void (*member_func)(TestRegFunc*, int);

void testRegFunc()
{
	TestRegFunc aaa;
	aaa.init();
	COMM_LOG("health[%d]", aaa.gethealth());
	void* func = RegfuncManager::instance().getFunc("modhealth");
	if (!func)
	{
		COMM_LOG("func pointer is null");
	}
	else
	{
		static_cast<member_func>(func)(&aaa, 5);
		COMM_LOG("health[%d]", aaa.gethealth());
	}
}

void testObjectManager()
{
	Logger::instance().redirect("haha.log");
	ObjectManager& inst = ObjectManager::instance();
	std::string id1 = inst.create("state");
	COMM_LOG("new object[%s]", id1.c_str());
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

int main()
{
	//testRegFunc();
	//testObjectManager();
	testStateManager();
	return 0;
}
