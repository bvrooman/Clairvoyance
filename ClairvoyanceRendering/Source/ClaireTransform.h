#ifndef CLAIRE_TRANSFORM_H
#define CLAIRE_TRANSFORM_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireVector.h"
#include "ClaireQuaternion.h"
#include "ClaireMatrix.h"

namespace Claire
{
	using math::Vector3;
	using math::Quaternion;
	using math::Matrix3;
	using math::Matrix4;

	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT Transform
	{
	public:
		Transform(
			const Vector3& translation = Vector3::ZERO,
			const Quaternion& rotation = Quaternion::IDENTITY,
			const Vector3& scale = Vector3::UNIT_SCALE
			);

		Transform(
			const Matrix4& homogeneous
			);

		inline bool operator == (const Transform& other) const;
		inline bool operator != (const Transform& other) const;

		inline bool isAffine(void) const;

		inline void translate(const Vector3& translation);
		inline void setTranslation(const Vector3& translation);
		inline Vector3 getTranslation(void) const;

		inline void rotate(const Quaternion& rotation);
		inline void setRotation(const Quaternion& rotation);
		inline void setRotation(const Matrix3& rotation);
		inline Matrix3 getRotationMatrix(void) const;
		inline Quaternion getRotationQuaternion(void) const;

		inline void scale(const Vector3& scale);
		inline void setScale(const Vector3& scale);
		inline Vector3 getScale(void) const;

		inline Matrix4 asHomogeneousMatrix(void) const;

		inline void buildFromHomogeneousMatrix(const Matrix4& homoegeneous);

	private:
		Matrix4 mMatrix;
	};

	CLAIRE_NAMESPACE_END
}

#endif