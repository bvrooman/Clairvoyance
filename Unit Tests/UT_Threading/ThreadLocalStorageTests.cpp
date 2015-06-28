#include <gtest\gtest.h>

#include "ClaireSTLContainers.h"
#include "Threading\ClaireThread.h"
#include "Threading\ClaireMutex.h"
#include "Threading\ClaireScopedLock.h"
#include "Threading\ClaireThreadLocalPtr.h"

#include <algorithm>

using namespace Claire;
using namespace Claire::core;

class ObjectManager
{
public:
	typedef map<string, int> IntMap;
	static IntMap sIntMap;
	static Mutex mutex;

	static void addInt(const string& name, int i)
	{
		ScopedLock<Mutex> l(mutex);
		IntMap::iterator it = sIntMap.find(name);
		if(it == sIntMap.end())
		{
			sIntMap.insert(IntMap::value_type(name, i));
		}
	}
};
ObjectManager::IntMap ObjectManager::sIntMap;
Mutex ObjectManager::mutex;

class TLSObject
{
public:
	static ThreadLocalPtr<int> tlsID;

	TLSObject(void)
	{
		std::cout << "CALL TO CREATE TLS OBJECT\n";

		if(tlsID.get() == nullptr)
		{
			std::cout << "Setting TLS ID...\n";
			tlsID = new int(ObjectManager::sIntMap.size());

			std::stringstream ss;
			ss << "TLS_" << this_thread::getID();
			string name = ss.str();
			ObjectManager::addInt(name, *tlsID);
		}
	}
};
ThreadLocalPtr<int> TLSObject::tlsID;

TEST(ThreadLocalStoragePtr, UnaryOperator)
{
	ThreadLocalPtr<unsigned int> i = new unsigned int(1);
	*i = 10;

	unsigned int b = *i;

	ASSERT_EQ(10, b);
}

void JustAThread(void)
{
	TLSObject* o = new TLSObject();
	TLSObject* o2 = new TLSObject();
}

TEST(ThreadLocalStorage, ThreadLocalPtrCount)
{
	// Create multiple objects in this thread
	// Only 1 ID should be added to the list
	TLSObject* o1 = new TLSObject();
	TLSObject* o2 = new TLSObject();
	TLSObject* o3 = new TLSObject();

	// Spawn a thread to create a new TLS int
	// This should add another ID to the list
	Thread thread1(JustAThread);
	thread1.join();

	// Spawn another thread
	// This should add another ID to the list
	Thread thread2(JustAThread);
	thread2.join();

	// Now, only 3 IDs should be added to the list

	typedef map<string, int> IntMap;
	IntMap map = ObjectManager::sIntMap;
	for(auto&& t : map)
	{
		std::cout << t.first << " : " << t.second << "\n";
	}

	ASSERT_EQ(3, map.size());
}