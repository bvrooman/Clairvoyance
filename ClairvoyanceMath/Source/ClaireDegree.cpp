#include "ClaireDegree.h"

#include "ClaireRadian.h"
#include "ClaireMath.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	Degree::Degree(const Radian& value)
		: mValue(value.valueDegrees())
	{
	}

	Degree& Degree::operator = (const Radian& rhs)
	{
		mValue = rhs.valueDegrees();
		return *this;
	}

	Degree Degree::operator + (const Radian& rhs) const
	{
		return Degree(mValue + rhs.valueDegrees());
	}

	Degree& Degree::operator += (const Radian& rhs)
	{
		mValue += rhs.valueDegrees();
		return *this;
	}

	Degree Degree::operator - (const Radian& rhs) const
	{
		return Degree(mValue - rhs.valueDegrees());
	}

	Degree& Degree::operator -= (const Radian& rhs)
	{
		mValue -= rhs.valueDegrees();
		return *this;
	}

	real Degree::valueRadians(void) const
	{
		return math_internals::degreesToRadians(mValue);
	}

	CLAIRE_NAMESPACE_END
}