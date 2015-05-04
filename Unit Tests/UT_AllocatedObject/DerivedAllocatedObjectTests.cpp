#include <gtest\gtest.h>

#include "Memory\ClaireMemoryConfig.h"

#include "Threading\ClaireThread.h"
#include "Threading\ClaireThreadGroup.h"

using namespace Claire;
using namespace Claire::core;

class MyClass
	: public GeneralAllocatedObject
{
public:
	MyClass(void)
		: j(0)
	{
		std::cout << "Constructing Class\n";
		doSomething();
	}

	virtual ~MyClass(void)
	{
		std::cout << "Destructing Class\n";
	}

	void doSomething(void)
	{
		std::cout << "Doing Something\n";
		for (int i = 0; i < 100; i++)
		{
			i += i * i;
		}
	}

	virtual void abstractFunc(void) = 0;

private:
	int j;
};

class MyDerivedClass
	: public MyClass
{
public:
	MyDerivedClass(void)
		: k(0)
	{
		std::cout << "Constructing Derived Class\n";
	}

	~MyDerivedClass(void)
	{
		std::cout << "Destructing Derived Class\n";
	}

	void abstractFunc(void)
	{}

private:
	int k;
};

TEST(DerivedAllocatedObject, Size)
{
	std::cout << sizeof(MyDerivedClass) << "\n";
}

TEST(DerivedAllocatedObject, PointerInstantiation)
{
	// Regular ptr instantiation
	MyClass* pTC = new MyDerivedClass();
	delete pTC;
}

TEST(DerivedAllocatedObject, ArrayInstantiation)
{
	// Array instantitation and deletion
	MyClass* aTC = new MyDerivedClass[5];
	delete[] aTC;
}

TEST(DerivedAllocatedObject, PlacementInstantiation)
{
	// Placement instantiation and deletion
	void* buf = operator new(1024);
	MyClass* t = new ((void*)buf) MyDerivedClass();
	t->~MyClass();
	operator delete(buf);
}

TEST(DerivedAllocatedObject, PlacementArrayInstantiation)
{
	// Placement array instantiation and deletion
	size_t instances = 5;
	void* buf = operator new(1024);
	// No polymorphism here because it crashes
	MyDerivedClass* t = new ((void*)buf) MyDerivedClass[instances];
	for (size_t i = 0; i < instances; i++)
	{
		t[i].~MyDerivedClass();
	}
	operator delete(buf);
}

TEST(DerivedAllocatedObject, UniquePtr)
{
	typedef std::unique_ptr<MyClass> MyClassUPtr;
	MyClassUPtr t = std::make_unique<MyDerivedClass>();
}