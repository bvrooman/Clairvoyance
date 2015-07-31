#include <gtest\gtest.h>

#include "ClaireSTLContainers.h"
#include "Threading\ClaireThread.h"
#include "Threading\ClaireThreadLocalPtr.h"
#include "Threading\ClaireMultipleInstanceTLS.h"

using namespace Claire;
using namespace Claire::core;

class Thing
{
public:
	Thing(void) { std::cout << "New Thing!\n"; }
	~Thing(void) { std::cout << "Delete Thing!\n"; }
};

class MITLSObject
{
public:
	string mName;
	static thread_local int mCount;
	MITLS<int> mMICount = 0;
	mutable MITLS<int*> mMIIntPtr;
	static thread_local Thing mThing;


	MITLSObject(const string& name)
		: mName(name)
	{
		std::cout << "Constructing " << mName << "\n";
		mCount++;
		mMICount++;
	}

	~MITLSObject(void)
	{
		std::cout << "Destructing " << mName << "\n";
	}

	void print(void) const
	{
		std::cout << std::dec << mName << " TLS count: " << mCount << " MITLS count: " << mMICount << " MIIntPtr: " << *getIntPtr() << "\n";
	}

	int* getIntPtr(void) const
	{
		if (!mMIIntPtr)
		{
			mMIIntPtr = new int(0);
		}
		return mMIIntPtr;
	}
};

thread_local int MITLSObject::mCount = 0;
thread_local Thing MITLSObject::mThing;

void JustAnotherThread(void)
{
	std::cout << "Entering " << this_thread::getID() << "\n";
		
	MITLSObject object1("Object_1");
	MITLSObject object2("Object_2");
	MITLSObject object3("Object_3");
	
	object1.print();
	object2.print();
	object3.print();

	std::cout << "Exiting " << this_thread::getID() << "\n";
}

TEST(InstancedTLS, InstancedTLS)
{
	std::thread thread1(JustAnotherThread);
	thread1.join();

	std::thread thread2(JustAnotherThread);
	thread2.join();

	std::thread thread3(JustAnotherThread);
	thread3.join();
}


void TheThread(
	MITLSObject& object1,
	MITLSObject& object2,
	MITLSObject& object3
	)
{
	std::cout << "Entering " << this_thread::getID() << "\n";

	object1.mCount++;
	object2.mCount++;
	object3.mCount++;

	object1.mMICount++;
	object2.mMICount++;
	object3.mMICount++;

	(*object1.getIntPtr())++;
	(*object2.getIntPtr())++;
	(*object3.getIntPtr())++;

	object1.print();
	object2.print();
	object3.print();

	std::cout << "Exiting " << this_thread::getID() << "\n";
}

TEST(InstancedTLS, Test2)
{
	MITLSObject object1("Object_1");
	MITLSObject object2("Object_2");
	MITLSObject object3("Object_3");

	object1.print();
	object2.print();
	object3.print();

	std::thread thread1(TheThread, object1, object2, object3);
	thread1.join();

	std::thread thread2(TheThread, object1, object2, object3);
	thread2.join();

	std::thread thread3(TheThread, object1, object2, object3);
	thread3.join();
}