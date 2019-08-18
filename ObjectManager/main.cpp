

#include "types/BaseObject.h"

int main()
{
	BaseObject* object = BaseFactoty::instance().create("state");
	object->init();
	delete object;
	return 0;
}
