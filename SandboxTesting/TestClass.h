#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <memory>
#include <string>
#include <iostream>

class Manager
{
public:
	Manager(void) {}
	~Manager(void) {}

	void* allocate(size_t sz)
	{
		return ::operator new(sz);
	}

	void deallocate(void* ptr)
	{
		std::cout << ptr << "\n";
		::operator delete(ptr);
	}
};

class TestClass
{
public:
	TestClass(void);
	~TestClass(void);

public:
	static void* operator new (size_t sz, Manager* manager)
	{
		void* ptr = manager->allocate(sz);
		std::cout << ptr << "\n";
		return ptr;
	}

	static void operator delete(void* ptr, Manager* manager)
	{
	}

	static void destroy(void* ptr, Manager* manager)
	{
		manager->deallocate(ptr);
	}

public:
	Manager* manager;
	int i;
};

class Deleter
{
public:
	void operator ()(TestClass* tc)
	{
		Manager* manager = tc->manager;
		tc->~TestClass();
		TestClass::destroy(tc, manager);
	}
};

typedef std::unique_ptr<TestClass, Deleter> TestClassUPtr;
typedef std::shared_ptr<TestClass> TestClassSPtr;

#endif