#ifndef CLAIRE_RENDERING_PLATFORM_H
#define CLAIRE_RENDERING_PLATFORM_H

namespace Claire
{
#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	if defined(CLAIRE_RENDERING_NONCLIENT_BUILD)
#		define CLAIRE_RENDERING_EXPORT __declspec(dllexport)
#	else
#		define CLAIRE_RENDERING_EXPORT __declspec(dllimport)
#	endif
#endif
}

#endif