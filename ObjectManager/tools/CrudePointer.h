

#pragma once

#include <exception>

template <typename T>
class CrudePointer
{
public:
	CrudePointer(T* rawPtr)
	{
		if (rawPtr == nullptr)
		{
			mRawIsNull = true;
			try
			{
				mPointer = new T;
			}
			catch (...)
			{
				exit(-1);
			}
		}
		else
		{
			mRawIsNull = false;
			mPointer = rawPtr;
		}
	}

	CrudePointer(const CrudePointer& pointer)
	{
		this->mPointer = pointer.mPointer;
		this->mRawIsNull = pointer.mRawIsNull;

		pointer.mPointer = nullptr;
		pointer.mRawIsNull = false;
	}

	~CrudePointer()
	{
		if (mRawIsNull && mPointer)
		{
			delete mPointer;
		}
	}

	T& operator*()
	{
		return *mPointer;
	}

private:
	T* mPointer;
	bool mRawIsNull;
};
