#include "ClaireMutex.h"

// Needed so that the implemented threading structure is a complete type
#include "ClaireThreadingIncludes.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	Mutex::Mutex(void)
		: pMutex()
	{
	}

	Mutex::~Mutex(void)
	{
	}

	void Mutex::lock(void)
	{
		pMutex->lock();
	}

	void Mutex::unlock(void)
	{
		pMutex->unlock();
	}

	Mutex::MutexImpl& Mutex::operator*(void)
	{
		return *pMutex;
	}

	CLAIRE_NAMESPACE_END
}