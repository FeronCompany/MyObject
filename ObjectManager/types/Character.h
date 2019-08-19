

#pragma once

#include "BaseObject.h"

struct CharaData
{
	std::string mID;
	std::string mName;

};

class Character : public BaseObject
{
public:
	Character();
	Character(Character&& instance);
	~Character();
	void init() override;
	void setNo(const std::string& no) override;

private:
	CharaData* mCharaInfo;
};
