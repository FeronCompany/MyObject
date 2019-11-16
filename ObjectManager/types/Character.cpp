

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

REG_TYPE(Character, chara);
