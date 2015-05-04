#ifndef CLAIRE_THREADING_PLATFORM_H
#define CLAIRE_THREADING_PLATFORM_H

#include "ClairePrerequisites.h"

#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	include "Win32\ClaireThreadPrimitives.h"
#	include "Win32\ClaireThreadDetails.h"
#endif

#endif