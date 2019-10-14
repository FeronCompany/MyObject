

#pragma once

#include <string>
#include <vector>
#include <map>

#include "CommSingleton.h"

struct TraitEffect
{
	std::string mEffectName;
	std::string mEffectDesc;
	std::string mEffectFuncName;
	int32_t mValue;
};
// trait of characters
class Trait
{
public:
	Trait(const std::string& name, const std::string& desc);
	void addEffect(TraitEffect* trait);
	std::vector<TraitEffect*>& getAllEffect();

private:
	std::string mTraitName;
	std::string mTraitDesc;
	std::vector<TraitEffect*> mEffectList;
};

// a place to store all known traits and effects
class TraitHub
{
	friend CommSingleton<TraitHub>;
public:
	~TraitHub();
	void init();

	Trait* getTrait(const std::string& traitName);
	TraitEffect* getEffect(const std::string& traitName);

private:
	void initTraits();
	void initEffect();
	TraitHub() {}

	std::map<std::string, Trait*> mTraitList;
	std::map<std::string, TraitEffect*> mEffectList;
};

typedef CommSingleton<TraitHub> CTraitHub;
