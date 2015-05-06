#ifndef CLAIRE_DEGREE_H
#define CLAIRE_DEGREE_H

#include "ClaireMathPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	class Radian;

	class CLAIRE_MATH_EXPORT Degree
	{
	public:
		explicit Degree(real value)
			: mValue(value)
		{}
		~Degree(void) = default;

		Degree& operator = (real f)
		{
			mValue = f;
			return *this;
		}
		Degree& operator = (const Degree& d)
		{
			mValue = d.mValue;
			return *this;
		}
		Degree operator + (void) const
		{
			return *this;
		}
		Degree operator - (void) const
		{
			return Degree(-mValue);
		}
		
		Degree operator + (const Degree& rhs) const
		{
			return Degree(mValue + rhs.mValue);
		}
		Degree& operator += (const Degree& rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}
		Degree operator - (const Degree& rhs) const
		{
			return Degree(mValue - rhs.mValue);
		}
		Degree& operator -= (const Degree& rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		Degree operator * (real f) const
		{
			return Degree(mValue * f);
		}
		Degree operator * (const Degree& rhs) const
		{
			return Degree(mValue * rhs.mValue);
		}
		Degree& operator *= (real f)
		{
			mValue *= f; return *this;
		}

		Degree operator / (real f) const
		{
			return Degree(mValue / f);
		}
		Degree operator / (const Degree& rhs) const
		{
			return Degree(mValue / rhs.mValue);
		}
		Degree& operator /= (real f)
		{
			mValue /= f; return *this;
		}

		real valueDegrees(void) const
		{
			return mValue;
		}

		bool operator == (const Degree& r) const
		{
			return mValue == r.mValue;
		}
		bool operator != (const Degree& r) const
		{
			return mValue != r.mValue;
		}
		bool operator < (const Degree& r) const
		{
			return mValue < r.mValue;
		}
		bool operator <= (const Degree& r) const
		{
			return mValue <= r.mValue;
		}
		bool operator >(const Degree& r) const
		{
			return mValue > r.mValue;
		}
		bool operator >= (const Degree& r) const
		{
			return mValue >= r.mValue;
		}

		Degree(const Radian& degree);
		Degree& operator = (const Radian& rhs);

		Degree operator + (const Radian& rhs) const;
		Degree& operator += (const Radian& rhs);
		Degree operator - (const Radian& rhs) const;
		Degree& operator -= (const Radian& rhs);

		real valueRadians(void) const;

		inline friend std::ostream& operator <<
			(std::ostream& o, const Degree& v)
		{
			o << "Degree(" << v.valueDegrees() << ")";
			return o;
		}

	private:
		real mValue;
	};

	inline Degree operator * (real a, const Degree& b)
	{
		return Degree(a * b.valueDegrees());
	}

	inline Degree operator / (real a, const Degree& b)
	{
		return Degree(a / b.valueDegrees());
	}

	inline Degree operator "" _deg(long double degrees)
	{
		return Degree(degrees);
	}
	
	CLAIRE_NAMESPACE_END
}

#endif