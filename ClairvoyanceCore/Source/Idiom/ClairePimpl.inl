#ifndef CLAIRE_PIMPL_IMPL_H
#define CLAIRE_PIMPL_IMPL_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T>
	template<typename ...Args>
	Pimpl<T>::Pimpl(Args&& ...args)
		: mImpl(new T(std::forward<Args>(args)...))
	{
	}

	template<typename T>
	Pimpl<T>::~Pimpl(void)
	{
	}

	template<typename T>
	T* Pimpl<T>::operator->(void)
	{
		return get();
	}

	template<typename T>
	T& Pimpl<T>::operator*(void)
	{
		return *get();
	}

	template<typename T>
	T* Pimpl<T>::operator->(void) const
	{
		return get();
	}

	template<typename T>
	T& Pimpl<T>::operator*(void) const
	{
		return *get();
	}

	CLAIRE_NAMESPACE_END
}

#endif