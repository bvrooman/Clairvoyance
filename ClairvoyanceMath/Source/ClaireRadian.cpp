#include "ClaireRadian.h"

#include "ClaireDegree.h"
#include "ClaireMath.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	Radian::Radian(const Degree& value)
		: mValue(value.valueRadians())
	{
	}

	Radian& Radian::operator = (const Degree& rhs)
	{
		mValue = rhs.valueRadians();
		return *this;
	}

	Radian Radian::operator + (const Degree& rhs) const
	{
		return Radian(mValue + rhs.valueRadians());
	}

	Radian& Radian::operator += (const Degree& rhs)
	{
		mValue += rhs.valueRadians();
		return *this;
	}

	Radian Radian::operator - (const Degree& rhs) const
	{
		return Radian(mValue - rhs.valueRadians());
	}

	Radian& Radian::operator -= (const Degree& rhs)
	{
		mValue -= rhs.valueRadians();
		return *this;
	}

	real Radian::valueDegrees(void) const
	{
		return math_internals::radiansToDegrees(mValue);
	}


	CLAIRE_NAMESPACE_END
}