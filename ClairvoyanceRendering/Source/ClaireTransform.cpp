#include "ClaireTransform.h"

#include "ClaireMath.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	Transform::Transform(
		const Vector3& translation,
		const Quaternion& rotation,
		const Vector3& scale
		)
		: mMatrix(Matrix4::IDENTITY)
	{
		setTranslation(translation);
		setRotation(rotation);
		setScale(scale);
	}

	Transform::Transform(
		const Matrix4& homogeneous
		)
	{
		buildFromHomogeneousMatrix(homogeneous);
	}

	bool Transform::operator == (const Transform& other) const
	{
		if(mMatrix != other.mMatrix)
		{
			return false;
		}
		return true;
	}

	bool Transform::operator != (const Transform& other) const
	{
		return !(*this == other);
	}

	bool Transform::isAffine(void) const
	{
		return mMatrix.isAffine();
	}

	void Transform::translate(const Vector3& translation)
	{
		Vector3 v = getTranslation() + translation;
		setTranslation(v);
	}

	void Transform::setTranslation(const Vector3& translation)
	{
		mMatrix[0][3] = translation.x;
		mMatrix[1][3] = translation.y;
		mMatrix[2][3] = translation.z;
	}

	Vector3 Transform::getTranslation(void) const
	{
		return Vector3(
			mMatrix[0][3],
			mMatrix[1][3],
			mMatrix[2][3]
			);
	}

	void Transform::rotate(const Quaternion& rotation)
	{
		Matrix3 m = getRotationMatrix() * rotation.asRotationMatrix();
		setRotation(m);
	}

	void Transform::setRotation(const Quaternion& rotation)
	{
		Matrix3 m = rotation.asRotationMatrix();
		setRotation(m);
	}

	void Transform::setRotation(const Matrix3& rotation)
	{
		mMatrix[0][0] = rotation[0][0]; mMatrix[0][1] = rotation[0][1]; mMatrix[0][2] = rotation[0][2];
		mMatrix[1][0] = rotation[1][0]; mMatrix[1][1] = rotation[1][1]; mMatrix[1][2] = rotation[1][2];
		mMatrix[2][0] = rotation[2][0]; mMatrix[2][1] = rotation[2][1]; mMatrix[2][2] = rotation[2][2];
	}

	Matrix3 Transform::getRotationMatrix(void) const
	{
		return Matrix3({
			mMatrix[0][0], mMatrix[0][1], mMatrix[0][2],
			mMatrix[1][0], mMatrix[1][1], mMatrix[1][2],
			mMatrix[2][0], mMatrix[2][1], mMatrix[2][2]
		});
	}

	Quaternion Transform::getRotationQuaternion(void) const
	{
		Quaternion q;
		q.buildFromRotationMatrix(
			getRotationMatrix()
			);
		return q;
	}

	void Transform::scale(const Vector3& scale)
	{
		Vector3 v = getScale() * scale;
		setScale(v);
	}

	void Transform::setScale(const Vector3& scale)
	{
		mMatrix[0][0] = scale.x;
		mMatrix[1][1] = scale.y;
		mMatrix[2][2] = scale.z;
	}

	Vector3 Transform::getScale(void) const
	{
		return Vector3(
			mMatrix[0][0],
			mMatrix[1][1],
			mMatrix[2][2]
			);
	}

	Matrix4 Transform::asHomogeneousMatrix(void) const
	{
		//Matrix4 m = Matrix4::IDENTITY;

		//// Set the position
		//m[0][3] = mTranslation[0];
		//m[1][3] = mTranslation[1];
		//m[2][3] = mTranslation[2];

		//// Set the rotation
		//math::Matrix3 rot = mRotation.asRotationMatrix();
		//m[0][0] = rot[0][0]; m[0][1] = rot[0][1]; m[0][2] = rot[0][2];
		//m[1][0] = rot[1][0]; m[1][1] = rot[1][1]; m[1][2] = rot[1][2];
		//m[2][0] = rot[2][0]; m[2][1] = rot[2][1]; m[2][2] = rot[2][2];

		//// Set the scale
		//if(mScale != Vector3::UNIT_SCALE)
		//{
		//	Matrix4 s = Matrix4::IDENTITY;
		//	s[0][0] = mScale.x;
		//	s[1][1] = mScale.y;
		//	s[2][2] = mScale.z;
		//	m = m * s;
		//}
		//
		//return m;

		return mMatrix;
	}

	void Transform::buildFromHomogeneousMatrix(const Matrix4& homogeneous)
	{
		//// Decompose the homogeneous transform matrix into its components
		//// http://www.robertblum.com/articles/2005/02/14/decomposing-matrices

		//Vector3 translation;
		//translation[0] = homogeneous[0][3];
		//translation[1] = homogeneous[1][3];
		//translation[2] = homogeneous[2][3];
		//mTranslation = translation;

		//math::Matrix3 rot;
		//rot[0][0] = homogeneous[0][0]; rot[0][1] = homogeneous[0][1]; rot[0][2] = homogeneous[0][2];
		//rot[1][0] = homogeneous[1][0]; rot[1][1] = homogeneous[1][1]; rot[1][2] = homogeneous[1][2];
		//rot[2][0] = homogeneous[2][0]; rot[2][1] = homogeneous[2][1]; rot[2][2] = homogeneous[2][2];
		//Quaternion rotation;
		//rotation.buildFromRotationMatrix(rot);
		//mRotation = rotation;

		//Vector3 scale;
		//scale[0] = Vector3(rot[0][0], rot[0][1], rot[0][2]).length();
		//scale[1] = Vector3(rot[1][0], rot[1][1], rot[1][2]).length();
		//scale[2] = Vector3(rot[2][0], rot[2][1], rot[2][2]).length();
		//if(rot.determinant() < 0)
		//{
		//	scale[0] *= -1;
		//}
		//mScale = scale;

		mMatrix = homogeneous;
	}
	
	CLAIRE_NAMESPACE_END
}