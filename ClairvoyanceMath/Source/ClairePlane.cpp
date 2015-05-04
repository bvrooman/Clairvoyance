#include "ClairePlane.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	Plane::Plane(void)
		: normal(Vector3::ZERO)
		, d(0)
	{
	}

	Plane::Plane(const Plane& rhs)
		: normal(rhs.normal)
		, d(rhs.d)
	{
	}

	Plane::Plane(const Vector3& normal, real constant)
		: normal(normal)
		, d(-constant)
	{
	}

	Plane::Plane(real a, real b, real c, real d)
		: normal(a, b, c)
		, d(d)
	{
	}

	real Plane::getDistance(const Vector3& point) const
	{
		return normal.dotProduct(point) + d;
	}

	CLAIRE_NAMESPACE_END
}