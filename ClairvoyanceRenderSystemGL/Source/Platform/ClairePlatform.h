#ifndef CLAIRE_GL_PLATFORM_H
#define CLAIRE_GL_PLATFORM_H

namespace Claire
{
#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	if defined(CLAIRE_GL_NONCLIENT_BUILD)
#		define CLAIRE_GL_EXPORT __declspec(dllexport)
#	else
#		define CLAIRE_GL_EXPORT __declspec(dllimport)
#	endif
#endif
}

#endif