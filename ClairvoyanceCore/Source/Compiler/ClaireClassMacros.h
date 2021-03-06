#ifndef CLAIRE_CLASS_MACROS_H
#define CLAIRE_CLASS_MACROS_H

#include "ClaireNonCopyMacros.h"
#include "ClaireMovableMacros.h"

#define CLAIRE_MOVABLE_ONLY(CLASS) \
	CLAIRE_MOVABLE(CLASS) \
	CLAIRE_NON_COPYABLE(CLASS)

#define CLAIRE_MOVABLE_COPYABLE(CLASS) \
	CLAIRE_MOVABLE(CLASS)

#endif