#ifndef CLAIRE_RADIAN_H
#define CLAIRE_RADIAN_H

#include "ClaireMathPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	class Degree;

	class CLAIRE_MATH_EXPORT Radian
	{
	public:
		explicit Radian(real value) 
			: mValue(value)
		{}
		~Radian(void) = default;

		Radian& operator = (real f)
		{ 
			mValue = f;
			return *this;
		}
		Radian& operator = (const Radian& rhs)
		{
			mValue = rhs.mValue;
			return *this;
		}
		Radian operator + (void) const
		{ 
			return *this;
		}
		Radian operator - (void) const
		{
			return Radian(-mValue);
		}

		Radian operator + (const Radian& rhs) const
		{
			return Radian(mValue + rhs.mValue);
		}
		Radian& operator += (const Radian& rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}
		Radian operator - (const Radian& rhs) const
		{
			return Radian(mValue - rhs.mValue);
		}
		Radian& operator -= (const Radian& rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		Radian operator * (real f) const
		{
			return Radian(mValue * f);
		}
		Radian operator * (const Radian& rhs) const
		{
			return Radian(mValue * rhs.mValue);
		}
		Radian& operator *= (real f)
		{
			mValue *= f; return *this;
		}

		Radian operator / (real f) const 
		{
			return Radian(mValue / f);
		}
		Radian operator / (const Radian& rhs) const
		{
			return Radian(mValue / rhs.mValue);
		}
		Radian& operator /= (real f)
		{
			mValue /= f; return *this;
		}

		real valueRadians(void) const
		{
			return mValue;
		}

		bool operator == (const Radian& r) const
		{
			return mValue == r.mValue;
		}
		bool operator != (const Radian& r) const
		{
			return mValue != r.mValue;
		}
		bool operator < (const Radian& r) const
		{
			return mValue < r.mValue;
		}
		bool operator <= (const Radian& r) const
		{
			return mValue <= r.mValue;
		}
		bool operator >(const Radian& r) const
		{
			return mValue > r.mValue;
		}
		bool operator >= (const Radian& r) const
		{
			return mValue >= r.mValue;
		}		

		Radian(const Degree& degree);
		Radian& operator = (const Degree& rhs);

		Radian operator + (const Degree& rhs) const;
		Radian& operator += (const Degree& rhs);
		Radian operator - (const Degree& rhs) const;
		Radian& operator -= (const Degree& rhs);

		real valueDegrees(void) const;

		inline friend std::ostream& operator <<
			(std::ostream& o, const Radian& v)
		{
			o << "Radian(" << v.valueRadians() << ")";
			return o;
		}

	private:
		real mValue;
	};

	inline Radian operator * (real a, const Radian& b)
	{
		return Radian(a * b.valueRadians());
	}

	inline Radian operator / (real a, const Radian& b)
	{
		return Radian(a / b.valueRadians());
	}

	CLAIRE_NAMESPACE_END
}

#endif