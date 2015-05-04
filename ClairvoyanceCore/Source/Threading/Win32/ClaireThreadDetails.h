#ifndef CLAIRE_THREADING_DETAILS_H
#define CLAIRE_THREADING_DETAILS_H

#include "ClairePrerequisites.h"

#include "ClaireThreadPrimitives.h"

namespace Claire
{

	CLAIRE_NAMESPACE_BEGIN(core)
	CLAIRE_NAMESPACE_BEGIN(threading_internal)

	inline native_handle_type getID(void)
	{
		return GetCurrentThreadId();
	}

	inline void yield(void)
	{
		Sleep(0);
	}

	CLAIRE_NAMESPACE_END
	CLAIRE_NAMESPACE_END
}

#endif