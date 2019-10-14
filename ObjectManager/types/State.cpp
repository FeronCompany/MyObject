

#include "State.h"
#include "BaseLogger.h"

State::State()
{
	population = 0;
}

State::State(const State& state)
{
	this->population = state.population;
}

State& State::operator=(const State& state)
{
	this->population = state.population;
	return *this;
}

State::~State()
{
}

void State::init()
{
	REG_MEMBER_FUNC_LITE(State, population);
}

void State::addTrait(const std::string& traitName)
{
	Trait* trait = CTraitHub::instance().getTrait(traitName);
	if (!trait)
	{
		COMM_LOG("no such trait[%s]", traitName.c_str());
		return;
	}
	mTraitList.push_back(trait);
}

std::string State::showTrait(const std::string& traitName)
{
	Trait* trait = CTraitHub::instance().getTrait(traitName);
	if (!trait)
	{
		COMM_LOG("no such trait[%s]", traitName.c_str());
		return "";
	}
	std::vector<TraitEffect*>& effectList = trait->getAllEffect();
	std::string effectDesc;
	for (auto& item : effectList)
	{
		effectDesc += item->mEffectDesc;
		effectDesc += "\n";
	}
	return effectDesc;
}

void State::calcuAttr()
{
	for (auto trait : mTraitList)
	{
		if (!trait)
		{
			COMM_LOG("no such trait");
			continue;
		}
		std::vector<TraitEffect*>& effectList = trait->getAllEffect();
		for (auto& item : effectList)
		{
			void* func = RegfuncManager::instance().getFunc(item->mEffectFuncName);
			if (!func)
			{
				COMM_LOG("effect callback func not exist[%s]", item->mEffectFuncName.c_str());
				continue;
			}
			static_cast<__stateActionFunc>(func)(this, item->mValue);
		}
	}
}

void State::modpopulation(int num)
{
	this->population += num;
	if (this->population < 0)
	{
		this->population = 0;
	}
}

REG_TYPE(state)
{
	State* object = SafeNew<State>();
	object->init();
	return object;
}
