

#include "CharaTrait.h"

void CharaTrait::calcu(CharaAttr* inputAttr, CharaAttr* attrModify)
{
	for (auto& item : mEffectList)
	{
		if(item.mCbFunc)
			item.mCbFunc(inputAttr, attrModify);
	}
}
