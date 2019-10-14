

#pragma once

#include <string>
#include <vector>

struct CharaTraitEffect
{
	std::string mEffectName;
	std::string mEffectDesc;
	std::string mEffectFuncName;
};
// trait of characters
class CharaTrait
{
public:
	void addEffect(const CharaTraitEffect& trait);
	const std::vector<CharaTraitEffect>& getAllEffect();

private:
	std::string mTraitName;
	std::string mTraitDesc;
	std::vector<CharaTraitEffect> mEffectList;
};
