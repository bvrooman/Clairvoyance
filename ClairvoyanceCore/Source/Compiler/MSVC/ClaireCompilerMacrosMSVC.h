#ifndef CLAIRE_COMPILER_MACROS_MSVC_H
#define CLAIRE_COMPILER_MACROS_MSVC_H

#define CLAIRE_ABSTRACT abstract

#define CLAIRE_PRAGMA(pragma) __pragma(pragma)

#define CLAIRE_ALIGN(alignment) __declspec(align(alignment))
#define CLAIRE_ALIGNED_SYMBOL(alignment, symbol) CLAIRE_ALIGN(alignment) symbol
#define CLAIRE_ALIGN_OF(type) __alignof(type)

#define CLAIRE_DISABLE_WARNING(number) CLAIRE_PRAGMA(warning(push)) CLAIRE_PRAGMA(warning(disable:number))
#define CLAIRE_ENABLE_WARNING(number) CLAIRE_PRAGMA(warning(pop))

//#define CLAIRE_THREAD_LOCAL thread_local
#define CLAIRE_THREAD_LOCAL __declspec(thread)

#endif