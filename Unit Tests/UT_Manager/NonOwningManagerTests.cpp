#include <gtest\gtest.h>

#include "Idiom\ClaireManager.h"

using namespace Claire;
using namespace Claire::core;

class MyManager
{
public:
	MyManager(void)
	{}

	int* create(const string& name, int value)
	{
		return mManager.create<int>(name, value);
	}

	void destroy(const string& name)
	{
		mManager.destroy(name);
	}

	void attach(const string& name, int*& p)
	{
		mManager.attach(name, p);
	}

	int* detach(const string& name)
	{
		return mManager.detach(name);
	}

	int* get(const string& name)
	{
		return mManager.get(name);
	}

private:
	Manager<int, string> mManager;
};


TEST(Manager, Get)
{
	MyManager manager;

	manager.create("Foo", 100);
	int i = *manager.get("Foo");
	ASSERT_EQ(100, i);
}

TEST(Manager, Create)
{
	MyManager manager;

	int i = *manager.create("Foo", 100);
	ASSERT_EQ(100, i);
}

TEST(Manager, Destroy)
{
	MyManager manager;

	manager.create("Foo", 100);
	int i = *manager.get("Foo");
	ASSERT_EQ(100, i);

	manager.destroy("Foo");
	int* p = manager.get("Foo");
	ASSERT_EQ(nullptr, p);
}

TEST(Manager, Attach)
{
	MyManager manager;

	int* p = new int(100);
	manager.attach("Foo", p);

	int i = *manager.get("Foo");
	ASSERT_EQ(100, i);
}

TEST(Manager, Detach)
{
	MyManager manager;

	manager.create("Foo", 100);

	int* p = manager.detach("Foo");
	int i = *p;
	ASSERT_EQ(100, i);

	int* p2 = manager.get("Foo");
	ASSERT_EQ(nullptr, p2);
}