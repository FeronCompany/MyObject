

#include "types/ObjectManager.h"
#include "tools/BaseLogger.h"

int main()
{
	ObjectManager& inst = ObjectManager::instance();
	std::string id1 = inst.create("state");
	Logger::instance().log(id1);
	std::string id2 = inst.create("state");
	Logger::instance().log(id2);
	std::string id3 = inst.create("chara");
	Logger::instance().log(id3);
	std::string id4 = inst.create("chara");
	Logger::instance().log(id4);
	inst.remove(id1);
	inst.remove(id2);
	inst.remove(id3);
	inst.remove(id4);
	return 0;
}
