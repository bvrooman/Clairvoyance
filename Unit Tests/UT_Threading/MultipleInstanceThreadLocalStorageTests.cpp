#include <gtest\gtest.h>

#include "ClaireSTLContainers.h"
#include "Threading\ClaireThread.h"
#include "Threading\ClaireThreadLocalPtr.h"
#include "Threading\ClaireMultipleInstanceTLS.h"

using namespace Claire;
using namespace Claire::core;

class MITLSObject
{
public:
	string mName;
	static thread_local int mCount;
	MITLS<int> mMICount = 0;

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
		std::cout << std::dec << mName << " TLS count: " << mCount << " MITLS count: " << mMICount << "\n";
	}
};

thread_local int MITLSObject::mCount = 0;

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
	std::cout << "\n";
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
	const MITLSObject& object1,
	const MITLSObject& object2,
	const MITLSObject& object3
	)
{
	std::cout << "Entering " << this_thread::getID() << "\n";

	object1.print();
	object2.print();
	object3.print();

	std::cout << "Exiting " << this_thread::getID() << "\n";
	std::cout << "\n";
}

TEST(InstancedTLS, Test2)
{
	MITLSObject object1("Object_1");
	MITLSObject object2("Object_2");
	MITLSObject object3("Object_3");

	std::thread thread1(TheThread, object1, object2, object3);
	thread1.join();

	std::thread thread2(TheThread, object1, object2, object3);
	thread2.join();

	std::thread thread3(TheThread, object1, object2, object3);
	thread3.join();
}