#include "Threading\ClaireThreadGroup.h"

#include "Threading\ClaireThread.h"
#include "Threading\ClaireScopedLock.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	ThreadGroup::ThreadGroup(void)
	{

	}

	ThreadGroup::~ThreadGroup(void)
	{
		for(ThreadList::iterator it = mThreadList.begin(), end = mThreadList.end();
			it != end;
			++it)
		{
			delete *it;
		}
	}

	bool ThreadGroup::containsThisThread(void)
	{
		Thread::ID id = this_thread::getID();
		ScopedLock<Mutex> lock(mMutex);

		for(ThreadList::iterator it = mThreadList.begin(), end = mThreadList.end();
			it != end;
			++it)
		{
			if ((*it)->getID() == id)
				return true;
		}
		return false;
	}

	bool ThreadGroup::containsThread(Thread* thread)
	{
		if (!thread)
			return false;

		Thread::ID id = this_thread::getID();
		ScopedLock<Mutex> lock(mMutex);

		for (ThreadList::iterator it = mThreadList.begin(), end = mThreadList.end();
			it != end;
			++it)
		{
			if ((*it)->getID() == id)
				return true;
		}
		return false;
	}

	void ThreadGroup::addThread(Thread* thread)
	{
		if(thread)
		{
			assert(!this->containsThread(thread));

			ScopedLock<Mutex> lock(mMutex);
			mThreadList.push_back(thread);
		}
	}

	void ThreadGroup::removeThread(Thread* thread)
	{
		ScopedLock<Mutex> lock(mMutex);

		for (ThreadList::iterator it = mThreadList.begin(), end = mThreadList.end();
			it != end;
			++it)
		{
			mThreadList.erase(it);
		}
	}

	void ThreadGroup::joinAll(void)
	{
		assert(!containsThisThread());

		ScopedLock<Mutex> lock(mMutex);

		for (ThreadList::iterator it = mThreadList.begin(), end = mThreadList.end();
			it != end;
			++it)
		{
			(*it)->join();
		}
	}

	CLAIRE_NAMESPACE_END
}