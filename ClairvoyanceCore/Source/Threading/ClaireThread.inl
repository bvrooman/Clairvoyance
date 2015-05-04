#include "ClaireThreadingIncludes.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename F, typename ...Args>
	Thread::Thread(F&& f, Args&& ...args)
		: pThread(std::forward<F>(f), std::forward<Args>(args)...)
	{
	}

	CLAIRE_NAMESPACE_END
}