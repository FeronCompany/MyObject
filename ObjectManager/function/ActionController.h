

#pragma once

#include <string>

#include "CommSingleton.h"
#include "BaseObject.h"

class ActionController
{
	friend CommSingleton<ActionController>;
public:
	void perform(const std::string& objectId, const std::string& action, int32_t value);

private:
	ActionController() {}

private:

};

typedef CommSingleton<ActionController> CActionController;
typedef void (*__objectAction)(BaseObject*, int);
