

#include "Character.h"
#include "BaseLogger.h"

Character::Character()
{
	
}

Character::~Character()
{
	
}

void Character::init()
{
	COMM_LOG("character");
}

REG_TYPE(chara)
{
	Character* object = SafeNew<Character>();
	object->init();
	return object;
}
