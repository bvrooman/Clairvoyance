#include "gtest\gtest.h"

#include <stdio.h>

#include "ClaireDegree.h"
#include "ClaireRadian.h"
#include "ClaireMath.h"

using namespace Claire;
using namespace math;

TEST(Degree, ToRadians)
{
	Degree a(270);
	real expected = (3 * PI) / 2;
	ASSERT_EQ(expected, a.valueRadians());
}

TEST(Degree, Literal)
{
	Degree d = 270.0_deg;
	std::cout << d << "\n";
	ASSERT_EQ(270, d.valueDegrees());
}

TEST(Radian, ToDegrees)
{
	Radian a((3 * PI) / 2);
	real expected = 270;
	ASSERT_EQ(expected, a.valueDegrees());
}

TEST(Radian, Literal)
{
	Radian d = 270.0_rad;
	std::cout << d << "\n";
	ASSERT_EQ(270, d.valueRadians());
}
