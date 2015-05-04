#include "ClaireRecursiveMutex.h"

// Needed so that the implemented threading structure is a complete type
#include "ClaireThreadingIncludes.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	RecursiveMutex::RecursiveMutex(void)
		: pRecursiveMutex()
	{
	}

	RecursiveMutex::~RecursiveMutex(void)
	{
	}

	void RecursiveMutex::lock(void)
	{
		pRecursiveMutex->lock();
	}

	void RecursiveMutex::unlock(void)
	{
		pRecursiveMutex->unlock();
	}

	RecursiveMutex::MutexImpl& RecursiveMutex::operator*(void)
	{
		return *pRecursiveMutex;
	}

	CLAIRE_NAMESPACE_END
}