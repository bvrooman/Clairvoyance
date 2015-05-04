#ifndef CLAIRE_MATH_H
#define CLAIRE_MATH_H

#include "ClaireMathPrerequisites.h"

#include "ClaireDegree.h"
#include "ClaireRadian.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	inline real tan(const Radian& value) { return (real)std::tan(value.valueRadians()); }
	inline real sin(const Radian& value) { return (real)std::sin(value.valueRadians()); }
	inline real cos(const Radian& value) { return (real)std::cos(value.valueRadians()); }

	inline real tan(real fValue) { return (real)std::tan(fValue); }
	inline real sin(real fValue) { return (real)std::sin(fValue); }
	inline real cos(real fValue) { return (real)std::cos(fValue); }
	
	inline Radian atan(real fValue) { return Radian(std::atan(fValue)); }
	inline Radian asin(real fValue) { return Radian(std::asin(fValue)); }
	inline Radian acos(real fValue) { return Radian(std::acos(fValue)); }

	inline real sqrt(real fValue) { return (real)std::sqrt(fValue); }
	inline real sqr(real fValue) { return fValue * fValue; }

	inline real abs(real fValue) { return (real)std::abs(fValue); }

	//Constants
	const real PI = (real)4.0 * (real)std::atan(1.0);

	CLAIRE_NAMESPACE_BEGIN(math_internals)

	const real DEG_TO_RAD = PI / (real)180.0;
	const real RAD_TO_DEG = (real)180.0 / PI;

	inline real degreesToRadians(real degrees)
	{
		return degrees * DEG_TO_RAD;
	}

	inline real radiansToDegrees(real radians)
	{
		return radians * RAD_TO_DEG;
	}

	CLAIRE_NAMESPACE_END

	CLAIRE_NAMESPACE_END
}

#endif