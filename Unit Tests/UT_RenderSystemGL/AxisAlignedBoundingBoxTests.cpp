#include "gtest\gtest.h"

#include "ClaireAxisAlignedBoundingBox.h"
#include "ClaireTransform.h"
#include "ClaireQuaternion.h"

using namespace Claire::rendering;
using namespace Claire::math;

TEST(AxisAlignedBoundingBox, setExtents)
{
	Vector3 min(-1, -1, -1);
	Vector3 max(1, 1, 1);

	AxisAlignedBoundingBox aabb;
	aabb.setExtents(min, max);

	ASSERT_EQ(min, aabb.getMinimum());
	ASSERT_EQ(max, aabb.getMaximum());
}

TEST(AxisAlignedBoundingBox, Merge)
{
	AxisAlignedBoundingBox aabb;

	{
		Vector3 min(-1, -1, -1);
		Vector3 max(0, 0, 0);
		AxisAlignedBoundingBox aabbComponent(min, max);
		aabb.merge(aabbComponent);
	}
	{
		Vector3 min(0, 0, 0);
		Vector3 max(1, 1, 1);
		AxisAlignedBoundingBox aabbComponent(min, max);
		aabb.merge(aabbComponent);
	}

	Vector3 expectedMin(-1, -1, -1);
	Vector3 expectedMax(1, 1, 1);
	ASSERT_EQ(expectedMin, aabb.getMinimum());
	ASSERT_EQ(expectedMax, aabb.getMaximum());
}

TEST(AxisAlignedBoundingBox, ApplyTransform)
{
	float v = Claire::math::sqrt(2) / 2;
	Vector3 min(-v, -v, -v);
	Vector3 max(v, v, v);

	AxisAlignedBoundingBox aabb(min, max);

	Quaternion q;
	q.buildFromAngleAxis(Radian(Claire::math::PI / 4), Vector3(0, 1, 0).normalizedCopy());
	Transform transform(Vector3::ZERO, q);

	aabb.applyTransform(transform);

	std::cout << aabb.getMinimum() << "\n";
	std::cout << aabb.getMaximum() << "\n";
}