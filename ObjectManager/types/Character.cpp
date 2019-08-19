

#include "Character.h"
#include "../tools/BaseLogger.h"

Character::Character()
{
	mCharaInfo = new CharaData;
}

Character::Character(Character&& instance)
{
	if (instance.mCharaInfo)
	{
		this->mCharaInfo = instance.mCharaInfo;
		instance.mCharaInfo = nullptr;
	}
	else
	{
		mCharaInfo = new CharaData;
	}
}

Character::~Character()
{
	if (mCharaInfo)
		delete mCharaInfo;
}

void Character::init()
{
	Logger::instance().log("State::init()");
}

void Character::setNo(const std::string& no)
{
	mCharaInfo->mID = no;
}

REG_TYPE(chara)
{
	Character* object = new Character;
	object->init();
	return object;
}
