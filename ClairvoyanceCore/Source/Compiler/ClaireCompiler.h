#ifndef CLAIRE_COMPILER_H
#define CLAIRE_COMPILER_H

// Compiler enumeration
#define CLAIRE_COMPILER_MSVC	1

#if defined(_MSC_VER)
#	define CLAIRE_COMPILER CLAIRE_COMPILER_MSVC
#	define CLAIRE_COMPILER_VERSION _MSC_VER
#	include "MSVC\ClaireCompilerMSVC.h"

#else
// Cross-platform implementation of stdint.h
#	include "pstdint.h"

#endif

#ifndef CLAIRE_ABSTRACT
#	define CLAIRE_ABSTRACT = 0
#endif

#define CLAIRE_OVERRIDE override
#define CLAIRE_FINAL final
#define CLAIRE_OVERRIDE_FINAL CLAIRE_OVERRIDE CLAIRE_FINAL

#endif