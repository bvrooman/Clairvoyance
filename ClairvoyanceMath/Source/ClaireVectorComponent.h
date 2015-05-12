#ifndef CLAIRE_VECTOR_COMPONENT_H
#define CLAIRE_VECTOR_COMPONENT_H

#include "ClaireMathPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	template<typename T, size_t Size>
	struct VectorComponent
	{
		std::array<T, Size> mArr;

		static const size_t Size = Size;
	};

	template<typename T>
	struct VectorComponent<T, 2>
	{
		union
		{
			struct
			{
				T x;
				T y;
			};
			std::array<T, 2> mArr;
		};

		VectorComponent() = default;
		VectorComponent(T x, T y) : x(x), y(y) {}

		static const size_t Size = 2;
	};

	template<typename T>
	struct VectorComponent<T, 3>
	{
		union
		{
			struct
			{
				T x;
				T y;
				T z;
			};
			std::array<T, 3> mArr;
		};

		VectorComponent() = default;
		VectorComponent(T x, T y, T z) : x(x), y(y), z(z) {}

		static const size_t Size = 3;
	};

	template<typename T>
	struct VectorComponent<T, 4>
	{
		union
		{
			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
			std::array<T, 4> mArr;
		};

		VectorComponent() = default;
		VectorComponent(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		static const size_t Size = 4;
	};

	CLAIRE_NAMESPACE_END
}

#endif