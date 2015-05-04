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
	~MyClass(void)
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

private:
	int j;
};

TEST(AllocatedObject, Size)
{
	std::cout << sizeof(MyClass) << "\n";
}

TEST(AllocatedObject, PointerInstantiation)
{
	// Regular ptr instantiation
	MyClass* pTC = new MyClass();
	delete pTC;
}

TEST(AllocatedObject, ArrayInstantiation)
{
	// Array instantitation and deletion
	MyClass* aTC = new MyClass[5];
	delete[] aTC;
}

TEST(AllocatedObject, PlacementInstantiation)
{
	// Placement instantiation and deletion
	void* buf = operator new(1024);
	MyClass* t = new ((void*)buf) MyClass();
	t->~MyClass();
	// Do not delete t, but rather delete the placement buffer
	// Why is there no placement delete?
	// See http://www.stroustrup.com/bs_faq2.html#placement-delete
	operator delete(buf);
}

TEST(AllocatedObject, PlacementArrayInstantiation)
{
	// Placement array instantiation and deletion
	size_t instances = 5;
	void* buf = operator new(1024);
	MyClass* t = new ((void*)buf) MyClass[instances];
	for(size_t i = 0; i < instances; i++)
	{
		t[i].~MyClass();
	}
	operator delete(buf);
}

TEST(AllocatedObject, UniquePtr)
{
	typedef std::unique_ptr<MyClass> MyClassUPtr;
	MyClassUPtr t = std::make_unique<MyClass>();
}