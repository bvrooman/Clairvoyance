#ifndef CLAIRE_PLATFORM_H
#define CLAIRE_PLATFORM_H

namespace Claire
{
// Platform enumeration
#define CLAIRE_PLATFORM_WIN32	1
#define CLAIRE_PLATFORM_LINUX	2

// Architecture enumeration
#define CLAIRE_ARCHITECTURE_32	1
#define CLAIRE_ARCHITECTURE_64	2


#if defined(__WIN32__) || defined(_WIN32)
#	define CLAIRE_PLATFORM CLAIRE_PLATFORM_WIN32
#endif

#if defined(_WIN64) || defined(WIN64) || defined(_M_IA64) || defined(_M_X64)
#	define CLAIRE_ARCHITECTURE CLAIRE_ARCHITECTURE_64
#else
#	define CLAIRE_ARCHITECTURE CLAIRE_ARCHITECTURE_32
#endif

#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	if defined(CLAIRE_CORE_NONCLIENT_BUILD)
#		define CLAIRE_CORE_EXPORT __declspec(dllexport)
#	else
#		define CLAIRE_CORE_EXPORT __declspec(dllimport)
#	endif
#endif

}

#endif