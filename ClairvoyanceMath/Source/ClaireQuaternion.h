#ifndef CLAIRE_QUATERNION_H
#define CLAIRE_QUATERNION_H

#include "ClaireMathPrerequisites.h"

#include "ClaireVector.h"
#include "ClaireMatrix.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	class Radian;

	// No CLAIRE_MATH_EXPORT here because shit's fucked
	// TODO: Fix this class. It's a mess.
	class Quaternion
		: public Vector4
	{
	public:
		Quaternion(real w = 1.0, real x = 0.0, real y = 0.0, real z = 0.0)
			: Vector4(x, y, z, w) {}

		Vector3 CLAIRE_MATH_EXPORT operator * (const Vector3& vector) const;

		Quaternion CLAIRE_MATH_EXPORT operator * (const Quaternion& quaternion) const;
		//Quaternion& operator *= (const Quaternion& quaternion);

		void CLAIRE_MATH_EXPORT buildFromAngleAxis(const Radian& rAngle, const Vector3& axis);
		void CLAIRE_MATH_EXPORT buildFromRotationMatrix(const Matrix3& rotationMatrix);
		void CLAIRE_MATH_EXPORT buildFromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

		Radian CLAIRE_MATH_EXPORT getAngle(void) const;
		Vector3 CLAIRE_MATH_EXPORT getAxis(void) const;

		Matrix3 CLAIRE_MATH_EXPORT asRotationMatrix(void) const;

		inline friend std::ostream& operator <<
			(std::ostream& o, const Quaternion& q)
		{
			o << "Quaternion( ";
			o << "w:" << q.w << " ";
			o << "x:" << q.x << " ";
			o << "y:" << q.y << " ";
			o << "z:" << q.z << " ";
			o << ")";
			return o;
		}

		static const CLAIRE_MATH_EXPORT Quaternion IDENTITY;
	};

	CLAIRE_NAMESPACE_END
}

#endif