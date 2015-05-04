#ifndef CLAIRE_COMPILER_MSVC_H
#define CLAIRE_COMPILER_MSVC_H

#include "ClaireCompilerMacrosMSVC.h"

// MSVC specific implementation of stdint.h
#include <stdint.h>

// Disable: "<type> needs to have dll-interface to be used by clients"
// Happens on nonpublic STL member variables; OK
CLAIRE_DISABLE_WARNING(4251)

#endif