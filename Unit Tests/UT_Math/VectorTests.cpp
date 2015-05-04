#include "gtest\gtest.h"

#include <stdio.h>

#include "ClaireVectorComponent.h"
#include "ClaireVector.h"

using namespace Claire;

TEST(Vector, Vector2Instantiation)
{
	math::Vector<2, real> a(1.0f, 2.0f);
	//ASSERT_EQ(sizeof(real) * 2, sizeof(a));
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(2, a.y);
}

TEST(Vector, Vector3Instantiation)
{
	math::Vector<3, real> a(1.0f, 2.0f, 3.0f);
	//ASSERT_EQ(sizeof(real) * 3, sizeof(a));
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(2, a.y);
	ASSERT_EQ(3, a.z);
}

TEST(Vector, Vector4Instantiation)
{
	math::Vector<4, real> a(1.0f, 2.0f, 3.0f, 4.0f);
	//ASSERT_EQ(sizeof(real) * 4, sizeof(a));
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(2, a.y);
	ASSERT_EQ(3, a.z);
	ASSERT_EQ(4, a.w);
}

TEST(Vector, DefaultConstructor)
{
	math::Vector<4> a;
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(0, a.z);
	ASSERT_EQ(0, a.w);
}

TEST(Vector, UnitInstantiation)
{
	math::Vector<4, real> a(1);
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(1, a.y);
	ASSERT_EQ(1, a.z);
	ASSERT_EQ(1, a.w);
}

TEST(Vector, CopyConstructor)
{
	math::Vector<4> a(1, 2, 3, 4);
	math::Vector<4> b(a);
	ASSERT_EQ(1, b.x);
	ASSERT_EQ(2, b.y);
	ASSERT_EQ(3, b.z);
	ASSERT_EQ(4, b.w);
}

TEST(Vector, InitializerListConstructor)
{
	math::Vector<4> a({ 1, 1, 1, 1 });
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(1, a.y);
	ASSERT_EQ(1, a.z);
	ASSERT_EQ(1, a.w);
}

TEST(Vector, ArrayConstructor)
{
	std::array<real, 4> _a{ { 1, 1, 1, 1 } };
	math::Vector<4> a(_a);
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(1, a.y);
	ASSERT_EQ(1, a.z);
	ASSERT_EQ(1, a.w);
}

TEST(Vector, OperatorIndex)
{
	math::Vector<3> a(1, 2, 3);
	a[0] = 5;
	a[1] = 5;
	a[2] = 5;

	ASSERT_EQ(5, a[0]);
	ASSERT_EQ(5, a[1]);
	ASSERT_EQ(5, a[2]);
}

TEST(Vector, OperatorEquals)
{
	math::Vector<3> a(0.0f, 0.0f, 0.0f);
	math::Vector<3> b(1.0f, 2.0f, 3.0f);
	a = b;
	ASSERT_EQ(1.0f, a.x);
	ASSERT_EQ(2.0f, a.y);
	ASSERT_EQ(3.0f, a.z);
}

TEST(Vector, OperatorNegative)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	a = -a;
	ASSERT_EQ(-1.0f, a.x);
	ASSERT_EQ(-2.0f, a.y);
	ASSERT_EQ(-3.0f, a.z);
}

TEST(Vector, Reciprocal)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	a = a.reciprocal();
	ASSERT_EQ(1.0f/1.0f, a.x);
	ASSERT_EQ(1.0f/2.0f, a.y);
	ASSERT_EQ(1.0f/3.0f, a.z);
}

TEST(Vector, OperatorPlus)
{
	math::Vector<3> a(0.0f, 0.0f, 0.0f);
	math::Vector<3> b(1.0f, 2.0f, 3.0f);
	a = a + b;
	ASSERT_EQ(1.0f, a.x);
	ASSERT_EQ(2.0f, a.y);
	ASSERT_EQ(3.0f, a.z);
}

TEST(Vector, OperatorPlusEquals)
{
	math::Vector<3> a(0.0f, 0.0f, 0.0f);
	math::Vector<3> b(1.0f, 2.0f, 3.0f);
	a += b;
	ASSERT_EQ(1.0f, a.x);
	ASSERT_EQ(2.0f, a.y);
	ASSERT_EQ(3.0f, a.z);
}

TEST(Vector, OperatorMinus)
{
	math::Vector<3> a(0.0f, 0.0f, 0.0f);
	math::Vector<3> b(1.0f, 2.0f, 3.0f);
	a = a - b;
	ASSERT_EQ(-1.0f, a.x);
	ASSERT_EQ(-2.0f, a.y);
	ASSERT_EQ(-3.0f, a.z);
}

TEST(Vector, OperatorMinusEquals)
{
	math::Vector<3> a(0.0f, 0.0f, 0.0f);
	math::Vector<3> b(1.0f, 2.0f, 3.0f);
	a -= b;
	ASSERT_EQ(-1.0f, a.x);
	ASSERT_EQ(-2.0f, a.y);
	ASSERT_EQ(-3.0f, a.z);
}

TEST(Vector, OperatorMultiply)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	math::Vector<3> b(2.0f, 3.0f, 4.0f);
	a = a * b;
	ASSERT_EQ(2.0f, a.x);
	ASSERT_EQ(6.0f, a.y);
	ASSERT_EQ(12.0f, a.z);
}

TEST(Vector, OperatorMultiplyEquals)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	math::Vector<3> b(2.0f, 3.0f, 4.0f);
	a *= b;
	ASSERT_EQ(2.0f, a.x);
	ASSERT_EQ(6.0f, a.y);
	ASSERT_EQ(12.0f, a.z);
}

TEST(Vector, OperatorMultiplyScalar)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	real f = 2;
	a = a * f;
	ASSERT_EQ(2.0f, a.x);
	ASSERT_EQ(4.0f, a.y);
	ASSERT_EQ(6.0f, a.z);
}

TEST(Vector, OperatorMultiplyEqualsScalar)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	real f = 2;
	a *= f;
	ASSERT_EQ(2.0f, a.x);
	ASSERT_EQ(4.0f, a.y);
	ASSERT_EQ(6.0f, a.z);
}

TEST(Vector, OperatorDivide)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	math::Vector<3> b(2.0f, 3.0f, 4.0f);
	a = a / b;
	ASSERT_EQ(1.0f / 2.0f, a.x);
	ASSERT_EQ(2.0f / 3.0f, a.y);
	ASSERT_EQ(3.0f / 4.0f, a.z);
}

TEST(Vector, OperatorDivideEquals)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	math::Vector<3> b(2.0f, 3.0f, 4.0f);
	a /= b;
	ASSERT_EQ(1.0f / 2.0f, a.x);
	ASSERT_EQ(2.0f / 3.0f, a.y);
	ASSERT_EQ(3.0f / 4.0f, a.z);
}

TEST(Vector, OperatorDivideScalar)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	real f = 2;
	a = a / f;
	ASSERT_EQ(1.0f / 2.0f, a.x);
	ASSERT_EQ(2.0f / 2.0f, a.y);
	ASSERT_EQ(3.0f / 2.0f, a.z);
}

TEST(Vector, OperatorDivideEqualsScalar)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	real f = 2;
	a /= f;
	ASSERT_EQ(1.0f / 2.0f, a.x);
	ASSERT_EQ(2.0f / 2.0f, a.y);
	ASSERT_EQ(3.0f / 2.0f, a.z);
}

TEST(Vector, OperatorCompareEquals)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	math::Vector<3> b(1.0f, 2.0f, 3.0f);
	ASSERT_EQ(a, b);
}

TEST(Vector, OperatorCompareNotEquals)
{
	math::Vector<3> a(1.0f, 2.0f, 3.0f);
	math::Vector<3> b(2.0f, 3.0f, 1.0f);
	ASSERT_NE(a, b);
}

TEST(Vector, Length)
{
	math::Vector<3> a(2.0f, 3.0f, 6.0f);
	real length = a.length();
	ASSERT_EQ(7.0f, length);
}

TEST(Vector, Normalize)
{
	math::Vector<3, float> a(2.0f, 3.0f, 6.0f);
	a.normalize();
	real length = a.length();
	ASSERT_FLOAT_EQ(1.0f, length);

	math::Vector<3, float> b(0.0f, 0.0f, 1.0f);
	b.normalize();
	math::Vector<3, float> c(0.0f, 0.0f, 1.0f);

	ASSERT_EQ(c, b);
}

TEST(Vector, DotProduct)
{
	math::Vector<3, float> a(1.0f, 2.0f, 3.0f);
	math::Vector<3, float> b(2.0f, 3.0f, 6.0f);
	real dotProduct = a.dotProduct(b);
	ASSERT_EQ(26.0f, dotProduct);
}

TEST(Vector, ZeroVector)
{
	math::Vector<3> a = math::Vector<3>::ZERO;
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(0, a.z);
}

TEST(Vector, UnitScaleVector)
{
	math::Vector<3> a = math::Vector<3>::UNIT_SCALE;
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(1, a.y);
	ASSERT_EQ(1, a.z);
}


TEST(Vector3, Instantiation)
{
	math::Vector3 a(1, 2, 3);
	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(2, a[1]);
	ASSERT_EQ(3, a[2]);
}

TEST(Vector3, DefaultConstructor)
{
	math::Vector3 a;
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(0, a.z);
}

TEST(Vector3, CopyConstructor)
{
	math::Vector3 a(1, 2, 3);
	math::Vector3 b(a);
	ASSERT_EQ(1, b.x);
	ASSERT_EQ(2, b.y);
	ASSERT_EQ(3, b.z);
}

TEST(Vector3, CrossProduct)
{
	math::Vector3 a(1, 2, 3);
	math::Vector3 b(-2, -3, -8);
	math::Vector3 c = a.crossProduct(b);
	math::Vector3 expected(-7, 2, 1);
	ASSERT_EQ(expected, c);
}

TEST(Vector3, UnitXVector)
{
	math::Vector3 a = math::Vector3::UNIT_X;
	ASSERT_EQ(1, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(0, a.z);
}

TEST(Vector3, UnitYVector)
{
	math::Vector3 a = math::Vector3::UNIT_Y;
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(1, a.y);
	ASSERT_EQ(0, a.z);
}

TEST(Vector3, UnitZVector)
{
	math::Vector3 a = math::Vector3::UNIT_Z;
	ASSERT_EQ(0, a.x);
	ASSERT_EQ(0, a.y);
	ASSERT_EQ(1, a.z);
}