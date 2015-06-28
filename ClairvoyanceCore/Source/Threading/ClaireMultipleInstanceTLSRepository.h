#ifndef CLAIRE_MULTIPLE_INSTANCE_TLS_REPOSITORY_H
#define CLAIRE_MULTIPLE_INSTANCE_TLS_REPOSITORY_H

#include "ClairePrerequisites.h"
#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template <typename T>
	class MultipleInstanceTLSRepository
	{
	protected:
		void store(uintptr_t instance, T value)
		{
			mRepository[instance] = value;
		}

		T load(uintptr_t instance) const
		{
			return mRepository[instance];
		}

		T& load(uintptr_t instance)
		{
			return mRepository[instance];
		}

		void remove(uintptr_t instance)
		{
			mRepository.erase(instance);
		}

	private:
		using Repository = map<uintptr_t, T>;
		static thread_local Repository mRepository;
	};

	template <typename T>
	typename thread_local MultipleInstanceTLSRepository<T>::Repository MultipleInstanceTLSRepository<T>::mRepository;

	CLAIRE_NAMESPACE_END
}

#endif