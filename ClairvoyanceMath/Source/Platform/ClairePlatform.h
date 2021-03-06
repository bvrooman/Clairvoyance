#ifndef CLAIRE_MATH_PLATFORM_H
#define CLAIRE_MATH_PLATFORM_H

namespace Claire
{
#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	if defined(CLAIRE_MATH_NONCLIENT_BUILD)
#		define CLAIRE_MATH_EXPORT __declspec(dllexport)
#	else
#		define CLAIRE_MATH_EXPORT __declspec(dllimport)
#	endif
#endif
}

#endif