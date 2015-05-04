#include "ClaireQuaternion.h"

#include "ClaireRadian.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)

	const Quaternion Quaternion::IDENTITY;

	Vector3 Quaternion::operator * (const Vector3& vector) const
	{
		Vector3 t = 2 * Vector3(x, y, z).crossProduct(vector);
		Vector3 rot = w * t + vector + Vector3(x, y, z).crossProduct(t);

		// Cheating to avoid floating point error
		for(int i = 0; i < 3; i++)
		{
			if(std::abs(rot[i]) <= 9e-008)
			{
				rot[i] = 0;
			}
		}

		return rot;
	}

	Quaternion Quaternion::operator * (const Quaternion& q) const
	{
		return Quaternion
		(
			w * q.w - x * q.x - y * q.y - z * q.z,
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x
		);
	}

	/*Quaternion& Quaternion::operator *= (const Quaternion& q)
	{
		Quaternion qR = *this * q;
		this->w = qR.w;
		this->x = qR.x;
		this->y = qR.y;
		this->z = qR.z;
		return *this;
	}*/

	void Quaternion::buildFromAngleAxis(const Radian& rAngle, const Vector3& axis)
	{
		Radian halfAngle(0.5 * rAngle);
		real sin = math::sin(halfAngle);
		w = math::cos(halfAngle);
		x = sin * axis.x;
		y = sin * axis.y;
		z = sin * axis.z;
	}

	void Quaternion::buildFromRotationMatrix(const Matrix3& rotationMatrix)
	{
		// Assume the trace + 1 > 0
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

		w = math::sqrt(std::max((real)0, 1 + rotationMatrix[0][0] + rotationMatrix[1][1] + rotationMatrix[2][2])) / 2;
		x = math::sqrt(std::max((real)0, 1 + rotationMatrix[0][0] - rotationMatrix[1][1] - rotationMatrix[2][2])) / 2;
		y = math::sqrt(std::max((real)0, 1 - rotationMatrix[0][0] + rotationMatrix[1][1] - rotationMatrix[2][2])) / 2;
		z = math::sqrt(std::max((real)0, 1 - rotationMatrix[0][0] - rotationMatrix[1][1] + rotationMatrix[2][2])) / 2;

		x = std::copysign(x, rotationMatrix[2][1] - rotationMatrix[1][2]);
		y = std::copysign(y, rotationMatrix[0][2] - rotationMatrix[2][0]);
		z = std::copysign(z, rotationMatrix[1][0] - rotationMatrix[0][1]);
	}

	void Quaternion::buildFromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		Matrix3 rot;

		rot[0][0] = xAxis.x;
		rot[1][0] = xAxis.y;
		rot[2][0] = xAxis.z;

		rot[0][1] = yAxis.x;
		rot[1][1] = yAxis.y;
		rot[2][1] = yAxis.z;

		rot[0][2] = zAxis.x;
		rot[1][2] = zAxis.y;
		rot[2][2] = zAxis.z;

		buildFromRotationMatrix(rot);
	}

	Radian Quaternion::getAngle(void) const
	{
		return 2 * acos(w);
	}

	Vector3 Quaternion::getAxis(void) const
	{
		Vector3 v;
		if(1 - w * w == 0)
		{
			v.x = x;
			v.y = y;
			v.z = z;
		}
		else
		{
			real s = math::sqrt(1 - w * w);
			v.x = x / s;
			v.y = y / s;
			v.z = z / s;
		}
		return v;
	}

	Matrix3 Quaternion::asRotationMatrix(void) const
	{
		real fTx = x + x;
		real fTy = y + y;
		real fTz = z + z;
		real fTwx = fTx * w;
		real fTwy = fTy * w;
		real fTwz = fTz * w;
		real fTxx = fTx * x;
		real fTxy = fTy * x;
		real fTxz = fTz * x;
		real fTyy = fTy * y;
		real fTyz = fTz * y;
		real fTzz = fTz * z;

		Matrix3 dest;
		dest[0][0] = 1.0f - (fTyy + fTzz);
		dest[0][1] = fTxy - fTwz;
		dest[0][2] = fTxz + fTwy;
		dest[1][0] = fTxy + fTwz;
		dest[1][1] = 1.0f - (fTxx + fTzz);
		dest[1][2] = fTyz - fTwx;
		dest[2][0] = fTxz - fTwy;
		dest[2][1] = fTyz + fTwx;
		dest[2][2] = 1.0f - (fTxx + fTyy);

		return dest;
	}

	CLAIRE_NAMESPACE_END
}