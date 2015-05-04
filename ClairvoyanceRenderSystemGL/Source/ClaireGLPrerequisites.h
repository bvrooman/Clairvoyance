#ifndef CLAIRE_GL_PREREQUISITES_H
#define CLAIRE_GL_PREREQUISITES_H

#include "ClaireRenderingPrerequisites.h"
#include "Platform\ClairePlatform.h"

// If using multithreading, enable GLEW multiple rendering contexts
#if CLAIRE_THREAD_SUPPORT == 1
#	define GLEW_MX
#endif

#include <gl\glew.h>

#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	define NOMINMAX
#	include <Windows.h>
#	include <gl\wglew.h>
#	include <GL\GLU.h>
#endif

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

#	define printOpenGLError() printOpenGLError__(__FILE__, __LINE__)
	inline int printOpenGLError__(char *file, int line)
	{
		GLenum glErr;
		int retCode = 0;

		glErr = glGetError();
		if (glErr != GL_NO_ERROR)
		{
			printf("OpenGL error in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
			retCode = 1;
		}
		return retCode;
	}

#if CLAIRE_THREAD_SUPPORT == 1

	GLEWContext* glewGetContext(void);

#	if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32

	WGLEWContext* wglewGetContext(void);

#	endif

	CLAIRE_NAMESPACE_END

#endif


}

#endif