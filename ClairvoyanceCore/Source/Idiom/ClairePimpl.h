#ifndef CLAIRE_PIMPL_H
#define CLAIRE_PIMPL_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T>
	class Pimpl
	{
	private:
		std::unique_ptr<T> mImpl;
		typedef typename std::unique_ptr<T>::pointer pointer;

	public:
		template<typename ...Args> Pimpl(Args&& ...args);
		~Pimpl(void);

		pointer get(void) const
		{
			return mImpl.get();
		}

		T* operator->(void);
		T& operator*(void);

		T* operator->(void) const;
		T& operator*(void) const;
	};

	CLAIRE_NAMESPACE_END
}

#include "ClairePimpl.inl"

#endif