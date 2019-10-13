

#pragma once

#include "BaseObject.h"
#include "CharaTrait.h"

class Character : public BaseObject
{
public:
	Character();
	Character(Character&& instance);
	~Character();
	void init() override;

private:
	CharaAttr* mCharaInfo;
	std::vector<CharaTrait> mTraitList;
};
