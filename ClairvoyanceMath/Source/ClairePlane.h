#ifndef CLAIRE_PLANE_H
#define CLAIRE_PLANE_H

#include "ClaireMathPrerequisites.h"

#include "ClaireVector.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	class CLAIRE_MATH_EXPORT Plane
	{
	public:
		Plane(void) = default;
		Plane(const Plane& rhs);
		Plane(const Vector3& normal, real constant);
		Plane(real a, real b, real c, real d);

		real getDistance(const Vector3& point) const;

	public:
		Vector3 normal = Vector3::ZERO;
		real d = 0;
	};

	CLAIRE_NAMESPACE_END
}

#endif