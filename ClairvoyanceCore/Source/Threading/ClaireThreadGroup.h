#ifndef CLAIRE_THREAD_GROUP_H
#define CLAIRE_THREAD_GROUP_H

#include "ClairePrerequisites.h"

#include "ClaireSTLContainers.h"

#include "Threading\ClaireMutex.h"
#include "Threading\ClaireThread.h"
#include "Threading\ClaireScopedLock.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT ThreadGroup
	{
	public:
		CLAIRE_MOVABLE_ONLY(ThreadGroup)

		ThreadGroup(void);
		~ThreadGroup(void);

		bool containsThisThread(void);
		bool containsThread(Thread* thread);

		void addThread(Thread* thread);
		void removeThread(Thread* thread);

		template<typename F>
		Thread* createThread(F threadFunc)
		{
			ScopedLock<Mutex> lock(mMutex);
			std::unique_ptr<Thread> newThread(new Thread(threadFunc));
			mThreadList.push_back(newThread.get());
			return newThread.release();
		}

		void joinAll(void);

	private:
		typedef list<Thread*> ThreadList;
		ThreadList mThreadList;
		Mutex mMutex;

	};

	CLAIRE_NAMESPACE_END
}
#endif