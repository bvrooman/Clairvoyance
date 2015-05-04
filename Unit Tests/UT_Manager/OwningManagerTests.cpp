#include <gtest\gtest.h>

#include "Idiom\ClaireManager.h"

using namespace Claire;
using namespace Claire::core;

class MyOwningManager
{
public:
	MyOwningManager(void)
	{}

	int* create(const string& name, int value)
	{
		return mManager.create<int>(name, value);
	}

	void destroy(const string& name)
	{
		mManager.destroy(name);
	}

	void attach(const string& name, std::unique_ptr<int>& p)
	{
		mManager.attach(name, p);
	}

	std::unique_ptr<int> detach(const string& name)
	{
		return mManager.detach(name);
	}

	int* get(const string& name)
	{
		return mManager.get(name);
	}

private:
	OwningManager<int, string> mManager;
};


TEST(OwningManager, Get)
{
	MyOwningManager manager;

	manager.create("Foo", 100);
	int i = *manager.get("Foo");
	ASSERT_EQ(100, i);
}

TEST(OwningManager, Create)
{
	MyOwningManager manager;

	int i = *manager.create("Foo", 100);
	ASSERT_EQ(100, i);
}

TEST(OwningManager, Destroy)
{
	MyOwningManager manager;

	manager.create("Foo", 100);
	int i = *manager.get("Foo");
	ASSERT_EQ(100, i);

	manager.destroy("Foo");
	int* p = manager.get("Foo");
	ASSERT_EQ(nullptr, p);
}

TEST(OwningManager, Attach)
{
	MyOwningManager manager;

	std::unique_ptr<int> up = std::make_unique<int>(100);
	manager.attach("Foo", up);

	int i = *manager.get("Foo");
	ASSERT_EQ(100, i);
}

TEST(OwningManager, Detach)
{
	MyOwningManager manager;

	manager.create("Foo", 100);

	std::unique_ptr<int> up = manager.detach("Foo");
	int i = *up.get();
	ASSERT_EQ(100, i);

	int* p = manager.get("Foo");
	ASSERT_EQ(nullptr, p);
}