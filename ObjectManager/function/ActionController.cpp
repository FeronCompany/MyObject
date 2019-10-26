

#include "ActionController.h"
#include "MemberFuncRegister.h"
#include "ObjectManager.h"
#include "ComposedLog.h"

void ActionController::perform(const std::string& objectId, const std::string& action, int32_t value)
{
	BaseObject* obj = CObjectManager::instance().refer(objectId);
	__objectAction;
	void* ptr = RegfuncManager::instance().getFunc(action);
	if (ptr == nullptr)
	{
		RECORD_LOG("[%s] is not a valid member function!", action.c_str());
		return;
	}
	static_cast<__objectAction>(ptr)(obj, value);
}
