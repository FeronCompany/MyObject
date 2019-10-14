

#include "CharaTrait.h"

void CharaTrait::addEffect(const CharaTraitEffect& trait)
{
	mEffectList.push_back(trait);
}

const std::vector<CharaTraitEffect>& CharaTrait::getAllEffect()
{
	return mEffectList;
}
