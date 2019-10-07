

#include "types/ObjectManager.h"
#include "BaseLogger.h"

int main()
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
	return 0;
}
