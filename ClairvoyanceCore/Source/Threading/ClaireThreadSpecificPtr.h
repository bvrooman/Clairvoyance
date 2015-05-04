#ifndef CLAIRE_THREAD_SPECIFIC_PTR_H
#define CLAIRE_THREAD_SPECIFIC_PTR_H

#include "ClairePrerequisites.h"

#include "ClaireThreadingTypes.h"
#include "ClaireThreadingIncludes.h"

#include "Idiom\ClairePimpl.h"

#include <thread>
#include <mutex>

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T> using ThreadSpecificPtr = threading_internal::ThreadSpecificPtrImpl<T>;

	CLAIRE_NAMESPACE_END
}

#endif