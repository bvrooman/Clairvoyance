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

TEST(Radian, ToDegrees)
{
	Radian a((3 * PI) / 2);
	real expected = 270;
	ASSERT_EQ(expected, a.valueDegrees());
}