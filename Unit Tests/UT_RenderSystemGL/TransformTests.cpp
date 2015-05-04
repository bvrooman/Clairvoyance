#include "gtest\gtest.h"

#include "ClaireTransform.h"

using namespace Claire;
using namespace Claire::rendering;

TEST(Transform, ComponentInstantiation)
{
	Vector3 translation = Vector3::ZERO;
	Quaternion rotation = Quaternion::IDENTITY;
	Vector3 scale = Vector3::UNIT_SCALE;
	Transform transform(translation, rotation, scale);
	ASSERT_EQ(translation, transform.getTranslation());
	ASSERT_EQ(rotation, transform.getRotationQuaternion());
	ASSERT_EQ(scale, transform.getScale());
}

TEST(Transform, HomogeneousMatrixInstantiation)
{
	Matrix4 m = Matrix4::IDENTITY;
	Transform transform(m);
	Vector3 translation = Vector3::ZERO;
	Quaternion rotation = Quaternion::IDENTITY;
	Vector3 scale = Vector3::UNIT_SCALE;
	ASSERT_EQ(translation, transform.getTranslation());
	ASSERT_EQ(rotation, transform.getRotationQuaternion());
	ASSERT_EQ(scale, transform.getScale());
}

TEST(Transform, AsHomogeneousMatrix)
{
	Vector3 translation = Vector3::ZERO;
	Quaternion rotation = Quaternion::IDENTITY;
	Vector3 scale = Vector3::UNIT_SCALE;
	Transform transform(translation, rotation, scale);
	Matrix4 m = Matrix4::IDENTITY;
	ASSERT_EQ(m, transform.asHomogeneousMatrix());
}