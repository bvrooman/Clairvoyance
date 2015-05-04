#include "gtest\gtest.h"

#include <stdio.h>

#include "ClaireMatrix.h"
#include "ClaireVector.h"

using namespace Claire;

TEST(Matrix, Matrix33Instantiation)
{
	math::Matrix<3, 3> m({
		0, 1, 2,
		3, 4, 5,
		6, 7, 8
	});

	ASSERT_EQ(0, m[0][0]);
	ASSERT_EQ(1, m[0][1]);
	ASSERT_EQ(2, m[0][2]);
	ASSERT_EQ(3, m[1][0]);
	ASSERT_EQ(4, m[1][1]);
	ASSERT_EQ(5, m[1][2]);
	ASSERT_EQ(6, m[2][0]);
	ASSERT_EQ(7, m[2][1]);
	ASSERT_EQ(8, m[2][2]);
}

TEST(Matrix, Matrix44Instantiation)
{
	math::Matrix<4, 4> m({
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15
	});

	ASSERT_EQ(0, m[0][0]);
	ASSERT_EQ(1, m[0][1]);
	ASSERT_EQ(2, m[0][2]);
	ASSERT_EQ(3, m[0][3]);
	ASSERT_EQ(4, m[1][0]);
	ASSERT_EQ(5, m[1][1]);
	ASSERT_EQ(6, m[1][2]);
	ASSERT_EQ(7, m[1][3]);
	ASSERT_EQ(8, m[2][0]);
	ASSERT_EQ(9, m[2][1]);
	ASSERT_EQ(10, m[2][2]);
	ASSERT_EQ(11, m[2][3]);
	ASSERT_EQ(12, m[3][0]);
	ASSERT_EQ(13, m[3][1]);
	ASSERT_EQ(14, m[3][2]);
	ASSERT_EQ(15, m[3][3]);
}

TEST(Matrix, Matrix34Instantiation)
{
	math::Matrix<3, 4> m({
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
	});

	ASSERT_EQ(0, m[0][0]);
	ASSERT_EQ(1, m[0][1]);
	ASSERT_EQ(2, m[0][2]);
	ASSERT_EQ(3, m[0][3]);
	ASSERT_EQ(4, m[1][0]);
	ASSERT_EQ(5, m[1][1]);
	ASSERT_EQ(6, m[1][2]);
	ASSERT_EQ(7, m[1][3]);
	ASSERT_EQ(8, m[2][0]);
	ASSERT_EQ(9, m[2][1]);
	ASSERT_EQ(10, m[2][2]);
	ASSERT_EQ(11, m[2][3]);
}

TEST(Matrix, OperatorIndex)
{
	math::Matrix<2, 2> m({
		0, 1,
		2, 3
	});
	m[0][0] = 5;
	m[0][1] = 5;
	m[1][0] = 5;
	m[1][1] = 5;

	ASSERT_EQ(5, m[0][0]);
	ASSERT_EQ(5, m[0][1]);
	ASSERT_EQ(5, m[1][0]);
	ASSERT_EQ(5, m[1][1]);
}

TEST(Matrix, OperatorPlus)
{
	math::Matrix<2, 2> a({
		0, 1,
		2, 3
	});
	math::Matrix<2, 2> b({
		2, 2,
		2, 2
	});
	math::Matrix<2, 2> c = a + b;
	ASSERT_EQ(2, c[0][0]);
	ASSERT_EQ(3, c[0][1]);
	ASSERT_EQ(4, c[1][0]);
	ASSERT_EQ(5, c[1][1]);
}

TEST(Matrix, OperatorPlusEquals)
{
	math::Matrix<2, 2> a({
		0, 1,
		2, 3
	});
	math::Matrix<2, 2> b({
		2, 2,
		2, 2
	});
	a += b;
	ASSERT_EQ(2, a[0][0]);
	ASSERT_EQ(3, a[0][1]);
	ASSERT_EQ(4, a[1][0]);
	ASSERT_EQ(5, a[1][1]);
}

TEST(Matrix, OperatorMinus)
{
	math::Matrix<2, 2> a({
		0, 1,
		2, 3
	});
	math::Matrix<2, 2> b({
		2, 2,
		2, 2
	});
	math::Matrix<2, 2> c = a - b;
	ASSERT_EQ(-2, c[0][0]);
	ASSERT_EQ(-1, c[0][1]);
	ASSERT_EQ(0, c[1][0]);
	ASSERT_EQ(1, c[1][1]);
}

TEST(Matrix, OperatorMinusEquals)
{
	math::Matrix<2, 2> a({
		0, 1,
		2, 3
	});
	math::Matrix<2, 2> b({
		2, 2,
		2, 2
	});
	a -= b;
	ASSERT_EQ(-2, a[0][0]);
	ASSERT_EQ(-1, a[0][1]);
	ASSERT_EQ(0, a[1][0]);
	ASSERT_EQ(1, a[1][1]);
}

TEST(Matrix, Concatenation)
{
	math::Matrix<2, 3> a({
		0, 1, 2,
		3, 4, 5
	});
	math::Matrix<3, 2> b({
		0, 3,
		1, 4,
		2, 5
	});
	math::Matrix<2, 2> expected({
		5, 14,
		14, 50
	});
	math::Matrix<2, 2> product = a * b;
	ASSERT_EQ(expected, product);
}

TEST(Matrix, Transpose)
{
	math::Matrix<2, 3> m({
		0, 1, 2,
		3, 4, 5
	});
	math::Matrix<3, 2> expected({
		0, 3,
		1, 4,
		2, 5
	});
	math::Matrix<3, 2> transpose = m.transpose();
	ASSERT_EQ(expected, transpose);
}

TEST(Matrix, OperatorMultiply)
{
	math::Matrix<2, 3> a({
		0, 1, 2,
		3, 4, 5
	});
	math::Matrix<3, 2> b({
		0, 3,
		1, 4,
		2, 5
	});
	math::Matrix<2, 2> expected({
		5, 14,
		14, 50
	});
	math::Matrix<2, 2> product = a * b;
	ASSERT_EQ(expected, product);
}

TEST(Matrix, OperatorMultiplyEquals)
{
	math::Matrix<2, 2> a({
		0, 1,
		3, 4,
	});
	math::Matrix<2, 2> b({
		0, 3,
		1, 4,
	});
	math::Matrix<2, 2> expected({
		1, 4,
		4, 25
	});
	a *= b;
	ASSERT_EQ(expected, a);
}

TEST(Matrix, OperatorMultiplyVector)
{
	math::Matrix<3, 3> a({
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	math::Vector<3> b({
		1, 2, 3
	});
	math::Vector<3> expected({
		14, 32, 50
	});
	math::Vector<3> product = a * b;
	ASSERT_EQ(expected, product);
}

TEST(Matrix, IsAffine)
{
	math::Matrix<3, 3> nonAffineMatrix({
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	ASSERT_FALSE(nonAffineMatrix.isAffine());

	math::Matrix<3, 3> affineMatrix({
		1, 2, 3,
		4, 5, 6,
		0, 0, 1
	});
	ASSERT_TRUE(affineMatrix.isAffine());
}