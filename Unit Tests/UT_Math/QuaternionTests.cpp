#include "gtest\gtest.h"

#include <stdio.h>

#include "ClaireQuaternion.h"

using namespace Claire;
using namespace math;

TEST(Quaternion, Instantiation)
{
	Quaternion a;
	ASSERT_EQ(1, a.w);
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(0, a.z);
}

TEST(Quaternion, BuildFromAngleAxis)
{
	Quaternion a;
	a.buildFromAngleAxis(Degree(90), Vector3(0, 0, 1));
	ASSERT_EQ(cos(Degree(45)), a.w);
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(sin(Degree(45)), a.z);
}


TEST(Quaternion, BuildFromAngleAxisGeneralCase)
{
	Vector3 axis(0, 0, 1);
	axis.normalize();
	real degrees = 90;
	Quaternion a;
	a.buildFromAngleAxis(Degree(degrees), axis);
	ASSERT_EQ(cos(Degree(degrees / 2)), a.w);
	ASSERT_EQ(sin(Degree(degrees / 2)) * axis.x, a.x);
	ASSERT_EQ(sin(Degree(degrees / 2)) * axis.y, a.y);
	ASSERT_EQ(sin(Degree(degrees / 2)) * axis.z, a.z);
}

TEST(Quaternion, BuildFromRotationMatrix)
{
	Matrix3 rotation = Matrix3::IDENTITY;
	rotation[0][0] = -1 / (real)sqrt(2);
	rotation[0][1] = -1 / (real)sqrt(2);
	rotation[1][0] = +1 / (real)sqrt(2);
	rotation[1][1] = -1 / (real)sqrt(2);
	Quaternion a;
	a.buildFromRotationMatrix(rotation);
	Radian angle(3 * math::PI / 4); // 135 degrees CCW
	ASSERT_EQ(angle, a.getAngle());
	ASSERT_EQ(0, a.getAxis().x);
	ASSERT_EQ(0, a.getAxis().y);
	ASSERT_EQ(1, a.getAxis().z);
}

TEST(Quaternion, VectorRotation90)
{
	Vector3 axis(0, 0, -1);
	axis.normalize();
	real degrees = 90;
	Quaternion q;
	q.buildFromAngleAxis(Degree(degrees), axis);

	Vector3 a(0, 1, 0);
	Vector3 b = q * a;
	Vector3 expected(1, 0, 0);

	ASSERT_FLOAT_EQ(expected.x, b.x);
	ASSERT_FLOAT_EQ(expected.y, b.y);
	ASSERT_FLOAT_EQ(expected.z, b.z);
}

TEST(Quaternion, VectorRotation180)
{
	Vector3 axis(0, 0, -1);
	axis.normalize();
	real degrees = 180;
	Quaternion q;
	q.buildFromAngleAxis(Degree(degrees), axis);

	Vector3 a(0, 1, 0);
	Vector3 b = q * a;
	Vector3 expected(0, -1, 0);

	ASSERT_FLOAT_EQ(expected.x, b.x);
	ASSERT_FLOAT_EQ(expected.y, b.y);
	ASSERT_FLOAT_EQ(expected.z, b.z);
}

