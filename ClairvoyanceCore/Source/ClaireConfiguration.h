#ifndef CLAIRE_CONFIGURATION_H
#define CLAIRE_CONFIGURATION_H

#include "ClaireBuildSettings.h"

#include "Platform\ClairePlatform.h"
#include "Compiler\ClaireCompiler.h"

#if defined(_DEBUG) || defined(DEBUG)
#	define CLAIRE_DEBUG 1
#else
#	define CLAIRE_DEBUG 0
#endif

#ifndef CLAIRE_DOUBLE_PRECISION
#	define CLAIRE_DOUBLE_PRECISION 0
#endif




#endif