#include "gtest\gtest.h"

#include "ClaireSceneNode.h"

#include "ClaireSceneObject.h"
#include "ClaireAxisAlignedBoundingBox.h"

using namespace Claire;
using namespace Claire::rendering;

class DummySceneObject
	: public SceneObject
{
public:
	DummySceneObject(const string& name)
		: SceneObject(name)
	{
		mAABB.setExtents(
			Vector3(-1, -1, -1),
			Vector3(1, 1, 1)
			);
	}

	void calculateLocalAABB(void) CLAIRE_OVERRIDE
	{
		mLocalAABB = mAABB;
	}

	AxisAlignedBoundingBox mAABB;
};

TEST(SceneNode, translateAABB)
{
	SceneNode* n1 = new SceneNode();
	SceneNode* n2 = n1->createChild();
	SceneNode* n3 = n2->createChild();

	n1->attachSceneObject(new DummySceneObject("0"));
	n2->attachSceneObject(new DummySceneObject("1"));
	n3->attachSceneObject(new DummySceneObject("2"));

	n1->getTransform().translate(Vector3(0, 1, 0));
	n2->getTransform().translate(Vector3(0, 1, 0));
	n3->getTransform().translate(Vector3(0, 1, 0));

	n1->update();

	AxisAlignedBoundingBox expectedAABB1(Vector3(-1, 0, -1), Vector3(1, 4, 1));
	AxisAlignedBoundingBox expectedAABB2(Vector3(-1, 1, -1), Vector3(1, 4, 1));
	AxisAlignedBoundingBox expectedAABB3(Vector3(-1, 2, -1), Vector3(1, 4, 1));

	ASSERT_EQ(expectedAABB1, n1->getWorldAABB());
	ASSERT_EQ(expectedAABB2, n2->getWorldAABB());
	ASSERT_EQ(expectedAABB3, n3->getWorldAABB());
}