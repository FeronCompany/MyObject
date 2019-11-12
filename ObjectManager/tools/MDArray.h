

#pragma once

#include <cstdint>
#include <cstring>
#include <exception>

// 2D Array
template<typename DATA>
class TwoDArray
{
public:
	TwoDArray(int32_t width, int32_t height)
	{
		mDataBuf = new DATA[width * height];
		memset(mDataBuf, 0, width * height);
		mHeight = height;
		mWidth = width;
	}

	~TwoDArray()
	{
		if (mDataBuf)
		{
			delete[] mDataBuf;
		}
	}

	DATA& operator()(int32_t x, int32_t y)
	{
		if (x > mWidth || y > mHeight)
		{
			throw std::exception("over size!");
		}
		return mDataBuf[mWidth * y + x];
	}

private:

private:
	DATA*	mDataBuf;
	int32_t	mHeight;
	int32_t	mWidth;
};

// 3D Array
template<typename DATA>
class ThreeDArray
{
public:
	ThreeDArray(int32_t width, int32_t height, int32_t length)
	{
		mDataBuf = new DATA[width * height * length];
		memset(mDataBuf, 0, width * height * length);
		mHeight = height;
		mWidth = width;
		mLength = length;
	}

	~ThreeDArray()
	{
		if (mDataBuf)
		{
			delete[] mDataBuf;
		}
	}

	DATA& operator()(int32_t x, int32_t y, int32_t z)
	{
		if (x > mWidth || y > mHeight || z > mLength)
		{
			throw std::exception("over size!");
		}
		return mDataBuf[mWidth * mHeight * z + mWidth * y + x];
	}

private:

private:
	DATA* mDataBuf;
	int32_t	mHeight;
	int32_t	mWidth;
	int32_t	mLength;
};
