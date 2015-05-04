#include "ClaireThread.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	Thread::Thread(void)
		: pThread()
	{
	}

	Thread::ID Thread::getID(void) const
	{
		std::stringstream ss;
		ss << std::hex << pThread->get_id();
		Thread::native_handle_type native_id;
		std::istringstream(ss.str()) >> std::hex >> native_id;
		return native_id;
	}

	Thread::~Thread(void)
	{
	}

	void Thread::join(void)
	{
		pThread->join();
	}

	CLAIRE_NAMESPACE_END
}