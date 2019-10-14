

#include "Trait.h"

Trait::Trait(const std::string& name, const std::string& desc)
{
	mTraitName = name;
	mTraitDesc = desc;
}

void Trait::addEffect(TraitEffect* trait)
{
	mEffectList.push_back(trait);
}

std::vector<TraitEffect*>& Trait::getAllEffect()
{
	return mEffectList;
}

TraitHub::~TraitHub()
{
	for (auto& item : mTraitList)
	{
		if (item.second)
		{
			delete item.second;
			item.second = nullptr;
		}
	}
	for (auto& item : mEffectList)
	{
		if (item.second)
		{
			delete item.second;
			item.second = nullptr;
		}
	}
}

void TraitHub::init()
{
	initEffect();
	initTraits();
}

void TraitHub::initTraits()
{
	Trait* pacificState = new Trait("pacific_state", "The state is living in peace.");
	pacificState->addEffect(mEffectList["pop_growth"]);
	mTraitList.insert(std::make_pair("pacific_state", pacificState));
}

void TraitHub::initEffect()
{
	TraitEffect* effectPopGrowth = new TraitEffect;
	effectPopGrowth->mEffectName = "pop_growth";
	effectPopGrowth->mEffectDesc = "Change growth speed of population";
	effectPopGrowth->mEffectFuncName = "modpopulation";
	effectPopGrowth->mValue = 1000;
	mEffectList.insert(std::make_pair(effectPopGrowth->mEffectName, effectPopGrowth));
}

Trait* TraitHub::getTrait(const std::string& traitName)
{
	auto itor = mTraitList.find(traitName);
	if (itor == mTraitList.end())
	{
		return nullptr;
	}
	else
	{
		return itor->second;
	}
}

TraitEffect* TraitHub::getEffect(const std::string& traitName)
{
	auto itor = mEffectList.find(traitName);
	if (itor == mEffectList.end())
	{
		return nullptr;
	}
	else
	{
		return itor->second;
	}
}
