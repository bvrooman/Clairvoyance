#ifndef CLAIRE_PREREQUISITES_H
#define CLAIRE_PREREQUISITES_H

#include "ClaireConfiguration.h"
#include "Compiler\ClaireNamespaceMacros.h"
#include "Compiler\ClaireClassMacros.h"
#include "Casts\ClaireUnionCast.h"

#if CLAIRE_DOUBLE_PRECISION == 1
	typedef double real;
#else
	typedef float real;
#endif

namespace Claire
{
	typedef uint8_t byte;

	typedef unsigned short ushort;
	typedef unsigned int uint;
}

#include "ClaireSTDHeaders.h"

namespace Claire
{
	typedef std::string string;

}

#endif