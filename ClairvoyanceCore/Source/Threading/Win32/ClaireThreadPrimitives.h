#ifndef CLAIRE_THREADING_WIN32_H
#define CLAIRE_THREADING_WIN32_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	CLAIRE_NAMESPACE_BEGIN(threading_internal)

	extern "C"
	{
		__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
		__declspec(dllimport) void __stdcall Sleep(unsigned long);
	}

	typedef decltype(GetCurrentThreadId()) native_handle_type;

	CLAIRE_NAMESPACE_END
	CLAIRE_NAMESPACE_END
}

#endif