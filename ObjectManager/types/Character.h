

#pragma once

#include "BaseObject.h"
#include "Trait.h"

class Character : public BaseObject
{
public:
	Character();
	~Character();
	void init() override;

private:
	//CharaAttr* mCharaInfo;
	std::vector<Trait> mTraitList;
};
