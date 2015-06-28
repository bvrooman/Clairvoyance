#ifndef CLAIRE_MULTIPLE_INSTANCE_TLS_H
#define CLAIRE_MULTIPLE_INSTANCE_TLS_H

#include "ClairePrerequisites.h"
#include "ClaireMultipleInstanceTLSRepository.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	
	template <typename T>
	class MultipleInstanceTLS
		: public MultipleInstanceTLSRepository<T>
	{
	public:
		MultipleInstanceTLS(void) = default;

		~MultipleInstanceTLS(void)
		{
			remove(reinterpret_cast<uintptr_t>(this));
		}

		MultipleInstanceTLS(const T& value)
		{
			store(reinterpret_cast<uintptr_t>(this), value);
		}

		MultipleInstanceTLS& operator = (const T& value)
		{
			store(reinterpret_cast<uintptr_t>(this), value);
			return *this;
		}

		operator T(void) const
		{
			return load(reinterpret_cast<uintptr_t>(this));
		}

		operator T&(void)
		{
			return load(reinterpret_cast<uintptr_t>(this));
		}

		inline friend std::ostream& operator <<
			(std::ostream& o, const MultipleInstanceTLS& mitls)
		{
			o << (T)mitls;
			return o;
		}
	};

	template <typename T> using MITLS = MultipleInstanceTLS<T>;

	CLAIRE_NAMESPACE_END
}

#endif