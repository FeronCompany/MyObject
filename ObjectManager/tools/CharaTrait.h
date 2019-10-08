

#pragma once

#include <string>
#include <vector>

// basic attribute of characters
struct CharaAttr
{
	std::string mID;
	std::string mName;

};

typedef void (*CbAttrChange)(CharaAttr* input, CharaAttr* modify);

struct CharaTraitEffect
{
	std::string mEffectName;
	std::string mEffectDesc;
	CbAttrChange mCbFunc;
};
// trait of characters
struct CharaTrait
{
	std::string mTraitName;
	std::string mTraitDesc;

	void calcu(CharaAttr* inputAttr, CharaAttr* attrModify);

private:
	std::vector<CharaTraitEffect> mEffectList;
};

