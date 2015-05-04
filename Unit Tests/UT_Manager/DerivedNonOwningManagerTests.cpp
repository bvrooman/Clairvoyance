#include <gtest\gtest.h>

#include "Idiom\ClaireManager.h"
#include "DummyTypes.h"

using namespace Claire;
using namespace Claire::core;

class MyNonBaseOwningManager
{
protected:
	using Type = MyBaseType;

public:
	MyNonBaseOwningManager(void)
	{}

	virtual Type* create(const string& name) CLAIRE_ABSTRACT;

	void destroy(const string& name)
	{
		mManager.destroy(name);
	}

	void attach(const string& name, Type* p)
	{
		mManager.attach(name, p);
	}

	Type* detach(const string& name)
	{
		return mManager.detach(name);
	}

	Type* get(const string& name)
	{
		return mManager.get(name);
	}

protected:
	Manager<Type, string> mManager;
};

class MyDerivedOwningManager
	: public MyNonBaseOwningManager
{
public:
	MyNonBaseOwningManager::Type* create(const string& name) CLAIRE_OVERRIDE
	{
		return mManager.create<MyDerivedType>(name);
	}
};


TEST(DerivedNonOwningManager, Get)
{
	MyDerivedOwningManager manager;

	manager.create("Foo");
	MyBaseType* i = manager.get("Foo");
	ASSERT_EQ(100, i->foo());
}

TEST(DerivedNonOwningManager, Create)
{
	MyDerivedOwningManager manager;

	MyBaseType* i = manager.create("Foo");
	ASSERT_EQ(100, i->foo());
}

TEST(DerivedNonOwningManager, Destroy)
{
	MyDerivedOwningManager manager;

	manager.create("Foo");
	MyBaseType* i = manager.get("Foo");
	ASSERT_EQ(100, i->foo());

	manager.destroy("Foo");
	MyBaseType* p = manager.get("Foo");
	ASSERT_EQ(nullptr, p);
}

TEST(DerivedNonOwningManager, Attach)
{
	MyDerivedOwningManager manager;

	MyBaseType* p = new MyDerivedType();
	manager.attach("Foo", p);

	MyBaseType* i = manager.get("Foo");
	ASSERT_EQ(100, i->foo());
}

TEST(DerivedNonOwningManager, Detach)
{
	MyDerivedOwningManager manager;

	manager.create("Foo");

	MyBaseType* p = manager.detach("Foo");
	ASSERT_EQ(100, p->foo());

	MyBaseType* p2 = manager.get("Foo");
	ASSERT_EQ(nullptr, p2);
}