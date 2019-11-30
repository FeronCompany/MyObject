

#pragma once

#include <cstdint>
#include <cstring>
#include <exception>

// 2D Array
template<typename DATA>
class TwoDArray
{
public:
	TwoDArray(int32_t x, int32_t y)
	{
		mDataBuf = new DATA[x * y];
		memset(mDataBuf, 0, x * y);
		mY = y;
		mX = x;
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
		if (x > mX || y > mY)
		{
			throw std::exception("over size!");
		}
		return mDataBuf[mX * y + x];
	}

	void resize(int32_t x, int32_t y)
	{
		if (mDataBuf)
		{
			delete[] mDataBuf;
		}
		mDataBuf = new DATA[x * y];
		memset(mDataBuf, 0, x * y);
		mY = y;
		mX = x;
	}

private:

private:
	DATA* mDataBuf;
	int32_t	mY;
	int32_t	mX;
};

// 3D Array
template<typename DATA>
class ThreeDArray
{
public:
	ThreeDArray(int32_t x, int32_t y, int32_t z)
	{
		mDataBuf = new DATA[x * y * z];
		memset(mDataBuf, 0, x * y * z);
		mY = y;
		mX = x;
		mZ = z;
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
		if (x > mX || y > mY || z > mZ)
		{
			throw std::exception("over size!");
		}
		return mDataBuf[mX * mY * z + mX * y + x];
	}

	void resize(int32_t x, int32_t y, int32_t z)
	{
		if (mDataBuf)
		{
			delete[] mDataBuf;
		}
		mDataBuf = new DATA[x * y * z];
		memset(mDataBuf, 0, x * y * z);
		mY = y;
		mX = x;
		mZ = z;
	}

private:

private:
	DATA* mDataBuf;
	int32_t	mY;
	int32_t	mX;
	int32_t	mZ;
};

