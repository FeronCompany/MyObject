

#include "types/ObjectManager.h"
#include "tools/BaseLogger.h"

int main()
{
	ObjectManager& inst = ObjectManager::instance();
	std::string id = inst.create("state");
	Logger::instance().log(id);
	inst.remove(id);
	return 0;
}
