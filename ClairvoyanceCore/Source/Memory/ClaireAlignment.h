#ifndef CLAIRE_ALIGNMENT_H
#define CLAIRE_ALIGNMENT_H

#include "ClairePrerequisites.h"
#include "Compiler\ClaireCompiler.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	namespace alignment
	{
		// Implementing alignof:
		// We compute alignof using two separate algorithms, then take their min.

		namespace ffs
		{
			// alignof (T) must be a power of two which is a factor of sizeof (T).
			template <typename T>
			struct alignof
			{
				enum
				{
					s = sizeof(T),
					value = s ^ (s & (s - 1))
				};
			};
		}

		namespace quantumjump
		{
			// Put T in a struct, keep adding chars until a "quantum jump" in
			// the size occurs.
			template<typename T> struct alignof;

			template<int size_diff>
			struct helper
			{
				template<typename T>
				struct Val
				{
					enum { value = size_diff };
				};
			};

			template<>
			struct helper<0>
			{
				template<typename T>
				struct Val
				{
					enum { value = alignof<T>::value };
				};
			};

			template <typename T>
			struct alignof
			{
				struct Big
				{
					T x;
					char c;
				};

				enum
				{
					diff = sizeof(Big) - sizeof(T),
					value = helper<diff>::template Val<Big>::value
				};
			};

		} // QuantumJump

		template <typename T>
		struct alignof
		{
			enum
			{
				x = quantumjump::alignof<T>::value,
				y = ffs::alignof<T>::value,
				value = x < y ? x : y
			};
		};
	}

	CLAIRE_NAMESPACE_END
}

#endif