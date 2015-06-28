#pragma once

template<typename T>
class TSPtr
{
private:
	typedef T* pointer;
	static thread_local pointer mPtr;

public:
	pointer get(void) const
	{
		return mPtr;
	}

	void reset(pointer ptr)
	{
		if (mPtr && mPtr != ptr)
		{
			delete mPtr;
		}
		mPtr = ptr;
	}

	T* operator->(void) { return get(); }
	T& operator*(void) { return *get(); }

	T* operator->(void) const { return get(); }
	T& operator*(void) const { return *get(); }
};