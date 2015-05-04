#include <gtest\gtest.h>

#include "Idiom\ClaireManager.h"
#include "DummyTypes.h"

using namespace Claire;
using namespace Claire::core;

class MyBaseOwningManager
{
protected:
	using Type = MyBaseType;

public:
	MyBaseOwningManager(void)
	{}

	virtual Type* create(const string& name) CLAIRE_ABSTRACT;

	void destroy(const string& name)
	{
		mManager.destroy(name);
	}

	void attach(const string& name, std::unique_ptr<Type>& p)
	{
		mManager.attach(name, p);
	}

	MyBaseTypeUPtr detach(const string& name)
	{
		return mManager.detach(name);
	}

	Type* get(const string& name)
	{
		return mManager.get(name);
	}

protected:
	OwningManager<Type, string> mManager;
};

class MyDerivedOwningManager
	: public MyBaseOwningManager
{
public:
	MyBaseOwningManager::Type* create(const string& name) CLAIRE_OVERRIDE
	{
		return mManager.create<MyDerivedType>(name);
	}
};


TEST(DerivedOwningManager, Get)
{
	MyDerivedOwningManager manager;

	manager.create("Foo");
	MyBaseType* i = manager.get("Foo");
	ASSERT_EQ(100, i->foo());
}

TEST(DerivedOwningManager, Create)
{
	MyDerivedOwningManager manager;

	MyBaseType* i = manager.create("Foo");
	ASSERT_EQ(100, i->foo());
}

TEST(DerivedOwningManager, Destroy)
{
	MyDerivedOwningManager manager;

	manager.create("Foo");
	MyBaseType* i = manager.get("Foo");
	ASSERT_EQ(100, i->foo());

	manager.destroy("Foo");
	MyBaseType* p = manager.get("Foo");
	ASSERT_EQ(nullptr, p);
}

TEST(DerivedOwningManager, Attach)
{
	MyDerivedOwningManager manager;

	MyBaseTypeUPtr up = std::make_unique<MyDerivedType>();
	manager.attach("Foo", up);

	MyBaseType* i = manager.get("Foo");
	ASSERT_EQ(100, i->foo());
}

TEST(DerivedOwningManager, Detach)
{
	MyDerivedOwningManager manager;
	
	manager.create("Foo");

	MyBaseTypeUPtr up = manager.detach("Foo");
	MyBaseType* i = up.get();
	ASSERT_EQ(100, i->foo());

	MyBaseType* p = manager.get("Foo");
	ASSERT_EQ(nullptr, p);
}