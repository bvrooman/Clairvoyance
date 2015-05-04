#include "Memory\ClaireMemoryConfig.h"

#include <chrono>

using namespace Claire;

class ObjNewDelete
	: public AllocatedObjectNewDelete
{
public:
	ObjNewDelete(void)
		: mBool(false)
	{}

	void doIt(void)
	{
		mBool = true;
	}

private:
	bool mBool;
};

class ObjPool
	: public AllocatedObjectPool
{
public:
	ObjPool(void)
		: mBool(false)
	{}

	void doIt(void)
	{
		mBool = true;
	}

private:
	bool mBool;
};

class ObjLinear
	: public AllocatedObjectLinear
{
public:
	ObjLinear(void)
		: mBool(false)
	{}

	void doIt(void)
	{
		mBool = true;
	}

private:
	bool mBool;
};

class ObjNone
{
public:
	ObjNone(void)
		: mBool(false)
	{}

	void doIt(void)
	{
		mBool = true;
	}

private:
	bool mBool;
};


void func()
{
	const size_t sz = 10000;

	ObjNewDelete* objsNewDelete[sz];
	ObjPool* objsPool[sz];
	ObjLinear* objsLinear[sz];
	ObjNone* objsNone[sz];

	for (int i = 0; i < sz; i++)
	{
		objsNewDelete[i] = new ObjNewDelete();
		objsPool[i] = new ObjPool();
		objsLinear[i] = new ObjLinear();
		objsNone[i] = new ObjNone();
	}


	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (int j = 0; j < sz; j++)
			for (int i = 0; i < sz; i++)
			{
			objsNewDelete[i]->doIt();
			}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout
			<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
			<< "\n";
	}

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (int j = 0; j < sz; j++)
			for (int i = 0; i < sz; i++)
			{
			objsPool[i]->doIt();
			}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout
			<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
			<< "\n";
	}

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (int j = 0; j < sz; j++)
			for (int i = 0; i < sz; i++)
			{
			objsLinear[i]->doIt();
			}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout
			<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
			<< "\n";
	}

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (int j = 0; j < sz; j++)
			for (int i = 0; i < sz; i++)
			{
			objsNone[i]->doIt();
			}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout
			<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
			<< "\n";
	}
}

int main()
{
	func();

	system("PAUSE");

	return 0;
}