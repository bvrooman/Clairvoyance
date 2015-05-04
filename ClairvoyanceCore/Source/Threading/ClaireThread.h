#ifndef CLAIRE_THREAD_H
#define CLAIRE_THREAD_H

#include "ClairePrerequisites.h"

#include "ClaireThreadingTypes.h"
#include "ClaireThreadingPlatform.h"

#include "Idiom\ClairePimpl.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT Thread
	{
	public:
		class ID;

	public:
		CLAIRE_MOVABLE_ONLY(Thread)

		typedef threading_internal::ThreadImpl ThreadImpl;

		Thread(void);
		template<typename F, typename ...Args> Thread(F&& f, Args&& ...);
		~Thread(void);

		void join(void);

		ID getID() const;

	private:		
		Pimpl<ThreadImpl> pThread;

		typedef threading_internal::native_handle_type native_handle_type;
		native_handle_type getIDImpl(void) const;
	};

	class Thread::ID
	{
	public:
		typedef Thread::native_handle_type Data;

	private:
		Data mData;

	public:
		ID(const Data& data)
			: mData(data)
		{}

		ID()
			: mData(0)
		{}

		ID(const ID& other) :
			mData(other.mData)
		{}

	public:
		template<class charT, class traits>
		friend std::basic_ostream<charT, traits>& operator << 
			(std::basic_ostream<charT, traits>& os, const ID& x)
		{
			return os << std::hex << x.mData;
		}

		inline friend bool operator == (const core::Thread::ID& lhs, const core::Thread::ID& rhs)
		{
			return lhs.mData == rhs.mData;
		}

		inline friend bool operator != (const core::Thread::ID& lhs, const core::Thread::ID& rhs)
		{
			return !(lhs == rhs);
		}
	};

	CLAIRE_NAMESPACE_END

	CLAIRE_NAMESPACE_BEGIN(this_thread)

	inline void yield(void)
	{
		core::threading_internal::yield();
	}

	inline core::Thread::ID getID(void)
	{
		return core::threading_internal::getID();
	}

	CLAIRE_NAMESPACE_END
}

#include "ClaireThread.inl"

#endif