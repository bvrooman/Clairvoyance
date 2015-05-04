#ifndef CLAIRE_VECTOR_H
#define CLAIRE_VECTOR_H

#include "ClaireMathPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireVectorComponent.h"

#include "ClaireMath.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	template<size_t Size, typename T = real>
	class Vector
		: public VectorComponent<T, Size>
	{
	public:
		//static size_t Size = Size;

		Vector(T x, T y)
			: VectorComponent<T, Size>(x, y) {}

		Vector(T x, T y, T z)
			: VectorComponent<T, Size>(x, y, z) {}

		Vector(T x, T y, T z, T w)
			: VectorComponent<T, Size>(x, y, z, w) {}

		Vector(T f = (T)0)
		{
			std::fill(mArr.begin(), mArr.end(), f);
		}

		Vector(const Vector& vector)
		{
			memcpy_s(mArr.data(), sizeof(mArr), vector.mArr.data(), Size * sizeof(T));
		}

		Vector(const std::array<T, Size> data)
		{
			mArr = data;
		}

		inline T operator [] (const size_t i) const
		{
			assert(i < Size);
			return *(&x + i);
		}

		inline T& operator [] (const size_t i)
		{
			assert(i < Size);
			return *(&x + i);
		}

		inline Vector& operator = (const Vector& vector)
		{
			memcpy_s(mArr.data(), sizeof(mArr), vector.mArr.data(), Size * sizeof(T));
			return *this;
		}

		inline Vector operator + (void) const
		{
			return *this;
		}

		inline Vector operator - (void) const
		{
			Vector v = *this;
			for (int i = 0; i < Size; i++)
			{
				v.mArr[i] = -v.mArr[i];
			}
			return v;
		}

		inline Vector reciprocal(void) const
		{
			Vector v = *this;
			for (int i = 0; i < Size; i++)
			{
				v.mArr[i] = (T)1.0 / v.mArr[i];
			}
			return v;
		}

		inline Vector operator + (const Vector& vector) const
		{
			Vector v = *this;
			for(int i = 0; i < Size; i++)
			{
				v.mArr[i] += vector[i];
			}
			return v;
		}

		inline Vector& operator += (const Vector& vector)
		{
			for(int i = 0; i < Size; i++)
			{
				mArr[i] += vector[i];
			}
			return *this;
		}

		inline Vector operator - (const Vector& vector) const
		{
			return *this + -vector;
		}

		inline Vector& operator -= (const Vector& vector)
		{
			*this += -vector;
			return *this;
		}

		inline Vector operator * (const Vector& vector) const
		{
			Vector v = *this;
			for (int i = 0; i < Size; i++)
			{
				v.mArr[i] *= vector[i];
			}
			return v;
		}

		inline Vector& operator *= (const Vector& vector)
		{
			for(int i = 0; i < Size; i++)
			{
				mArr[i] *= vector[i];
			}
			return *this;
		}

		inline Vector operator * (T f) const
		{
			Vector v = *this;
			for (int i = 0; i < Size; i++)
			{
				v.mArr[i] *= f;
			}
			return v;
		}

		inline Vector& operator *= (T f)
		{
			for (int i = 0; i < Size; i++)
			{
				mArr[i] *= f;
			}
			return *this;
		}

		inline Vector operator / (const Vector& vector) const
		{
			return *this * vector.reciprocal();
		}

		inline Vector& operator /= (const Vector& vector)
		{
			*this *= vector.reciprocal();
			return *this;
		}

		inline Vector operator / (T f) const
		{
			return *this * Vector(f).reciprocal();
		}

		inline Vector& operator /= (T f)
		{
			*this *= Vector(f).reciprocal();
			return *this;
		}

		inline bool operator == (const Vector& vector) const
		{
			for(int i = 0; i < Size; i++)
			{
				if(mArr[i] != vector[i])
					return false;
			}
			return true;
		}

		inline bool operator != (const Vector& vector) const
		{
			return !(*this == vector);
		}

		inline real length(void) const
		{
			real sqrLen = squaredLength();
			return sqrt(sqrLen);
		}

		inline real squaredLength(void) const
		{
			real sum = 0;
			for(int i = 0; i < Size; i++)
			{
				real v = (real)mArr[i];
				sum += v * v;
			}
			return sum;
		}

		inline void normalize(void)
		{
			real len = length();
			if(len > 1e-08)
			{
				Vector r(len);
				*this *= r.reciprocal();
			}
		}

		inline Vector normalizedCopy(void) const
		{
			Vector vector = *this;
			vector.normalize();
			return vector;
		}

		inline real dotProduct(const Vector& vector) const
		{
			real sum = 0;
			for(int i = 0; i < Size; i++)
			{
				sum += mArr[i] * vector[i];
			}
			return sum;
		}

		inline void toAbsolute(void)
		{
			for(int i = 0; i < Size; i++)
			{
				mArr[i] = math::abs(mArr[i]);
			}
		}

		template<typename U>
		inline Vector<U::Columns, T> operator * (const U& matrix)
		{

		}

		inline friend std::ostream& operator <<
			(std::ostream& o, const Vector& vec)
		{
			o << "Vector( ";
			for (size_t i = 0; i < Size; ++i)
			{
				o << vec[i] << " ";
			}
			o << ")";
			return o;
		}

		// Constants
		static const Vector<Size, T> ZERO;
		static const Vector<Size, T> UNIT_SCALE;
	};
	template<size_t Size, typename T> const typename Vector<Size, T> Vector<Size, T>::ZERO(0);
	template<size_t Size, typename T> const typename Vector<Size, T> Vector<Size, T>::UNIT_SCALE(1);

	template<size_t Size, typename T>
	inline Vector<Size, T> operator * (T f, Vector<Size, T> vector)
	{
		return vector * t;
	}

	template<size_t Size, typename T>
	inline Vector<Size, T> operator / (T f, Vector<Size, T> vector)
	{
		return vector / t;
	}


	template<typename T = real>
	class Vector3T
		: public Vector<3, T>
	{
	public:
		Vector3T(void) {}

		Vector3T(T x, T y, T z)
			: Vector<3, T>(x, y, z) {}

		Vector3T(const Vector& v)
			: Vector<3, T>(v) {}

		inline Vector3T crossProduct(const Vector3T& vector) const
		{
			return Vector3T(
				y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}

		inline friend std::ostream& operator <<
			(std::ostream& o, const Vector3T& vec)
		{
			o << "Vector( ";
			for (size_t i = 0; i < 3; ++i)
			{
				o << vec[i] << " ";
			}
			o << ")";
			return o;
		}

		static const Vector3T UNIT_X;
		static const Vector3T UNIT_Y;
		static const Vector3T UNIT_Z;
	};
	template<typename T> const Vector3T<T> Vector3T<T>::UNIT_X(1, 0, 0);
	template<typename T> const Vector3T<T> Vector3T<T>::UNIT_Y(0, 1, 0);
	template<typename T> const Vector3T<T> Vector3T<T>::UNIT_Z(0, 0, 1);

	typedef Vector3T<real> Vector3;

	inline Vector3 operator * (real f, Vector3 vector)
	{
		return vector * f;
	}

	inline Vector3 operator / (real f, Vector3 vector)
	{
		return vector / f;
	}

	typedef Vector<2, real> Vector2;
	typedef Vector<4, real> Vector4;

	CLAIRE_NAMESPACE_END
}

#endif