#include "gtest\gtest.h"

#include "ClaireNode.h"
#include "ClaireDummyNode.h"

using namespace Claire;
using namespace Claire::rendering;

TEST(Node, DerivedTransform)
{
	Node* n1 = new DummyNode();
	Node* n2 = n1->createChild();
	Node* n3 = n2->createChild();

	n1->getTransform().translate(Vector3(0, 1, 0));
	n2->getTransform().translate(Vector3(0, 1, 0));
	n3->getTransform().translate(Vector3(0, 1, 0));

	n1->update();

	Vector3 expected(0, 3, 0);
	Vector3 actual = n3->getDerivedTransform().getTranslation();
	ASSERT_EQ(expected, actual);

	delete n1;
}

TEST(Node, AttachNode)
{
	NodeUPtr node1branch1 = std::make_unique<DummyNode>();
	Node* node2branch1 = node1branch1->createChild();
	Node* node3branch1 = node2branch1->createChild();

	node1branch1->getTransform().translate(Vector3(0, 1, 0));
	node2branch1->getTransform().translate(Vector3(0, 1, 0));
	node3branch1->getTransform().translate(Vector3(0, 1, 0));

	NodeUPtr node1branch2 = std::make_unique<DummyNode>();
	node1branch2->getTransform().translate(Vector3(0, 1, 0));
	Node* node2branch2 = node1branch2->createChild();
	node2branch2->getTransform().translate(Vector3(0, 1, 0));

	// Attach the second branch, node1branch, to the leaf node
	// of the first branch and transfer ownership
	Node* node1branch2p = node3branch1->attachChild(std::move(node1branch2));

	node1branch1->update();

	Vector3 expected(0, 5, 0);
	Vector3 actual = node2branch2->getDerivedTransform().getTranslation();
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(5, node1branch1->getTreeSize());
}

TEST(Node, DetachNode)
{
	NodeUPtr node1branch1 = std::make_unique<DummyNode>();
	Node* node2branch1 = node1branch1->createChild();
	Node* node3branch1 = node2branch1->createChild();
	Node* node4branch1 = node3branch1->createChild();
	Node* node5branch1 = node4branch1->createChild();

	node1branch1->getTransform().translate(Vector3(0, 1, 0));
	node2branch1->getTransform().translate(Vector3(0, 1, 0));
	node3branch1->getTransform().translate(Vector3(0, 1, 0));
	node4branch1->getTransform().translate(Vector3(0, 1, 0));
	node5branch1->getTransform().translate(Vector3(0, 1, 0));

	// Update the branch so that the derived positions are calculated
	// Otherwise, the detached branch will have incorrect derived positions
	node1branch1->update();

	// Detach node3 from node2 to create a second branch
	NodeUPtr node1branch2 = node2branch1->detachChild(node3branch1->getName());
	Node* node2branch2 = node1branch2->getChildNodeVector()[0];
	Node* node3branch2 = node2branch2->getChildNodeVector()[0];

	node1branch2->update();

	Vector3 expected1(0, 2, 0);
	Vector3 actual1 = node2branch1->getDerivedTransform().getTranslation();
	ASSERT_EQ(expected1, actual1);
	ASSERT_EQ(2, node1branch1->getTreeSize());

	Vector3 expected2(0, 5, 0);
	Vector3 actual2 = node3branch2->getDerivedTransform().getTranslation();
	ASSERT_EQ(expected2, actual2);
	ASSERT_EQ(3, node1branch2->getTreeSize());
}