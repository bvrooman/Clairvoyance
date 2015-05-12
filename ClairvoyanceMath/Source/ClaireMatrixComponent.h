#ifndef CLAIRE_MATRIX_COMPONENT_H
#define CLAIRE_MATRIX_COMPONENT_H

#include "ClaireMathPrerequisites.h"

#include "ClaireVector.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	template<typename T, size_t Rows, size_t Columns> 
	struct MatrixComponent
	{
		static const size_t Rows = Rows;
		static const size_t Columns = Columns;
		static const size_t Size = Rows * Columns;

		typedef std::array<T, Columns> Row;
		typedef std::array<T, Rows> Column;

		union
		{
			std::array<T, Size> mArr;
			std::array<Row, Rows> mArr2D;
		};

		MatrixComponent(void)
		{
			std::fill(mArr.begin(), mArr.end(), (T)0);
		}

		MatrixComponent(const MatrixComponent& matrix)
		{
			memcpy_s(mArr.data(), sizeof(mArr), matrix.mArr.data(), Size * sizeof(T));
		}

		MatrixComponent(std::array<T, Size> args)
		{
			mArr = args;
		}
	};

	CLAIRE_NAMESPACE_END
}

#endif