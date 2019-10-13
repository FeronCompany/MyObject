

#include "types/ObjectManager.h"
#include "BaseLogger.h"
#include "MemberFuncRegister.h"

class TestRegFunc
{
public:
	TestRegFunc() :health(0) {}
	DECLARE_MEMBER_FUNC(TestRegFunc, healthMod);

	void tell()
	{
		//std::cout << "health[" << health << "]\n";
		COMM_LOG("health[%d]", health);
	}

private:
	int32_t health;
};

void TestRegFunc::healthMod(int num)
{
	this->health += num;
}

REG_MEMBER_FUNC(TestRegFunc, healthMod);

typedef void (*member_func)(TestRegFunc*, int);

void testRegFunc()
{
	TestRegFunc aaa;
	aaa.tell();
	void* func = RegfuncManager::instance().getFunc("healthMod");
	static_cast<member_func>(func)(&aaa, 5);
	aaa.tell();
}

void testObjectManager()
{
	Logger::instance().redirect("haha.log");
	ObjectManager& inst = ObjectManager::instance();
	std::string id1 = inst.create("chara");
	COMM_LOG("new object[%s]", id1.c_str());
	std::string id2 = inst.create("chara");
	COMM_LOG("new object[%s]", id2.c_str());
	std::string id3 = inst.create("chara");
	COMM_LOG("new object[%s]", id3.c_str());
	std::string id4 = inst.create("chara");
	COMM_LOG("new object[%s]", id4.c_str());
	inst.remove(id1);
	inst.remove(id2);
	inst.remove(id3);
	inst.remove(id4);
}

int main()
{
	testRegFunc();
	return 0;
}
