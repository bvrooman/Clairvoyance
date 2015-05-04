#ifndef CLAIRE_MATRIX_H
#define CLAIRE_MATRIX_H

#include "ClaireMathPrerequisites.h"
#include "ClaireMatrixComponent.h"

#include "ClaireVector.h"
#include "ClaireMatrix.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	template<size_t Rows, size_t Columns, typename T = real>
	class Matrix
		: public MatrixComponent<T, Rows, Columns>
	{
	public:
		Matrix(void)
		{
			std::fill(mArr.begin(), mArr.end(), (T)0);
		}

		Matrix(std::array<T, Size> args)
			: MatrixComponent(args) {}

		Matrix(const Matrix& matrix)
		{
			memcpy_s(mArr.data(), sizeof(mArr), matrix.mArr.data(), Size * sizeof(T));
		}

		static Matrix buildIdentity(void)
		{
			assert(Rows == Columns);
			Matrix m;
			for(size_t i = 0; i < Rows; i++)
			{
				m[i][i] = 1;
			}
			return m;
		}

		inline const Row operator [] (size_t row) const
		{
			assert(row < Rows);
			return mArr2D[row];
		}

		inline Row& operator [] (size_t row)
		{
			assert(row < Rows);
			return mArr2D[row];
		}

		inline Matrix& operator = (const Matrix& matrix)
		{
			memcpy_s(mArr.data(), sizeof(mArr), matrix.mArr.data(), Size * sizeof(T));
			return *this;
		}

		inline Matrix operator + (void) const
		{
			return *this;
		}

		inline Matrix operator - (void) const
		{
			Matrix m = *this;
			for (int i = 0; i < Size; i++)
			{
				m.mArr[i] = -m.mArr[i];
			}
			return m;
		}

		inline Matrix operator + (const Matrix& matrix) const
		{
			Matrix m = *this;
			for(size_t i = 0; i < Rows; i++)
			{
				(Vector<Columns, T>&)m[i] += matrix[i];
			}
			return m;
		}

		inline Matrix& operator += (const Matrix& matrix)
		{
			*this = *this + matrix;
			return *this;
		}

		inline Matrix operator - (const Matrix& matrix) const
		{
			Matrix m = *this;
			for (size_t i = 0; i < Rows; i++)
			{
				(Vector<Columns, T>&)m[i] -= matrix[i];
			}
			return m;
		}

		inline Matrix& operator -= (const Matrix& matrix)
		{
			*this = *this - matrix;
			return *this;
		}

		template<typename U>
		inline Matrix<Rows, U::Columns, T> operator * (const U& matrix) const
		{
			return concatenate(matrix);
		}

		template<typename U>
		inline Matrix<Rows, U::Columns, T> operator *= (const U& matrix)
		{
			*this = this->concatenate(matrix);
			return *this;
		}

		inline Vector<Columns, T> operator * (const Vector<Columns, T>& vector) const
		{
			Matrix<Columns, 1, T> m = vector.mArr;
			Matrix<1, Columns, T> mT = m.transpose();
			Matrix<Columns, 1, T> mP = *this * m;
			return (Vector<Columns, T>)mP.mArr;
		}
		
		bool operator == (const Matrix& matrix) const
		{
			for(int i = 0; i < Size; i++)
			{
				if(mArr[i] != matrix.mArr[i])
					return false;
			}
			return true;
		}

		bool operator != (const Matrix& matrix) const
		{
			return !(*this == matrix);
		}

		inline Matrix<Columns, Rows> transpose(void) const
		{
			Matrix<Columns, Rows, T> m;
			for(size_t i = 0; i < Rows; i++)
			{
				for(size_t j = 0; j < Columns; j++)
				{
					m[j][i] = mArr2D[i][j];
				}
			}
			return m;
		}

		template<typename U>
		inline Matrix<Rows, U::Columns, T> concatenate(const U& matrix) const
		{
			assert(Columns == U::Rows);
			Matrix<U::Columns, U::Rows, T> transpose = matrix.transpose();
			Matrix<Rows, U::Columns> m;
			for (size_t i = 0; i < Rows; i++)
			{
				Vector<Columns, T> row1 = mArr2D[i];
				for (size_t j = 0; j < U::Columns; j++)
				{
					Vector<Columns, T> row2 = transpose[j];
					m[i][j] = row1.dotProduct(row2);
				}
			}
			return m;
		}

		inline T determinant(void) const
		{
			assert(Rows == Columns);
			T sum = 0;
			for (size_t i = 0; i < Rows; i++)
			{
				sum += mArr2D[i][i];
			}
			return sum;
		}

		inline bool isAffine(void) const
		{
			Row lastRow = mArr2D[Rows - 1];
			for(size_t i = 0; i < Columns - 1; i++)
			{
				if(lastRow[i] != 0)
				{
					return false;
				}
			}
			if(lastRow[Columns - 1] != 1)
			{
				return false;
			}
			return true;
		}

		inline friend std::ostream& operator <<
			(std::ostream& o, const Matrix& mat)
		{
			o << "Matrix(";
			for (size_t i = 0; i < Rows; ++i)
			{
				o << " row" << (unsigned)i << "{ ";
				for (size_t j = 0; j < Columns; ++j)
				{
					o << mat[i][j] << " ";
				}
				o << "}";
			}
			o << " )";
			return o;
		}

		static const Matrix<Rows, Columns, T> ZERO;
		static const Matrix<Rows, Columns, T> IDENTITY;
	};
	template<size_t Rows, size_t Columns, typename T> const typename Matrix<Rows, Columns, T> Matrix<Rows, Columns, T>::ZERO;
	template<size_t Rows, size_t Columns, typename T> const typename Matrix<Rows, Columns, T> Matrix<Rows, Columns, T>::IDENTITY = Matrix<Rows, Columns, T>::buildIdentity();

	typedef Matrix<3, 3, real> Matrix3;
	typedef Matrix<4, 4, real> Matrix4;

	CLAIRE_NAMESPACE_END
}

#endif