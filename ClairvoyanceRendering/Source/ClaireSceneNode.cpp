#include "ClaireSceneNode.h"

#include "ClaireSceneObject.h"
#include "ClaireSceneNodeChainAABBComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	NameGenerator SceneNode::sNameGenerator("UnnamedSceneNode");

	SceneNode::SceneNode(
		const string& name,
		const Transform& transform
		)
		: Node(name, transform)
		, mSceneObjectAABBReference(nullptr)
		, mWorldAABBReference(nullptr)
	{
		setup();
	}

	SceneNode::SceneNode(
		const Transform& transform
		)
		: Node(transform)
		, mSceneObjectAABBReference(nullptr)
		, mWorldAABBReference(nullptr)
	{
		setup();
	}

	void SceneNode::setup(void)
	{
		INodeChainComponent* aabbComp = mNodeChain->createComponent<SceneNodeChainAABBComponent>();

		NodeChain::UpdatePass* postorderPass = mNodeChain->createUpdatePass(NodeChain::UPO_POST_ORDER);
		postorderPass->addComponent(aabbComp);
	}

	void SceneNode::update_(void)
	{
		updateSceneObjectAABB();
	}

	void SceneNode::updateSceneObjectAABB(void)
	{
		if(mSceneObjectAABBReference)
		{
			mSceneObjectAABBReference->clear();

			for_each(mSceneObjectMap.begin(), mSceneObjectMap.end(), [&](SceneObjectMap::value_type& type)
			{
				type.second->calculateWorldAABB();

				mSceneObjectAABBReference->merge(
					type.second->getWorldAABB()
					);
			});
		}

		for_each(mChildNodeVector.begin(), mChildNodeVector.end(), [](Node* node)
		{
			SceneNode* sceneNode = static_cast<SceneNode*>(node);
			sceneNode->updateSceneObjectAABB();
		});
	}

	SceneNode::SceneNode(
		NodeChainSPtr nodeChain,
		const string& name,
		const Transform& transform
		)
		: Node(nodeChain, name, transform)
		, mSceneObjectAABBReference(nullptr)
		, mWorldAABBReference(nullptr)
	{
	}

	SceneNode::SceneNode(
		NodeChainSPtr nodeChain,
		const Transform& transform
		)
		: Node(nodeChain, transform)
		, mSceneObjectAABBReference(nullptr)
		, mWorldAABBReference(nullptr)
	{
	}

	SceneNode::~SceneNode(void)
	{
	}

	SceneNode* SceneNode::createChild(
		const string& name,
		const Transform& transform
		)
	{
		Node* node = Node::createChild(name, transform);
		return (SceneNode*)node;
	}

	SceneNode* SceneNode::createChild(
		const Transform& transform
		)
	{
		return createChild(
			sNameGenerator.generate(),
			transform
			);
	}

	void SceneNode::attachSceneObject(SceneObject* sceneObject)
	{
		string name = sceneObject->getName();

		auto it = mSceneObjectMap.find(name);
		if(it != mSceneObjectMap.end())
		{
			// 
		}
		mSceneObjectMap.insert(SceneObjectMap::value_type(name, sceneObject));

		sceneObject->attachToSceneNode(this);
	}

	AxisAlignedBoundingBox SceneNode::getWorldAABB(void) const
	{
		if(mWorldAABBReference)
		{
			return *mWorldAABBReference;
		}
		return AxisAlignedBoundingBox();
	}

	void SceneNode::setSceneObjectAABBReference(AxisAlignedBoundingBox* aabb)
	{
		mSceneObjectAABBReference = aabb;
	}

	void SceneNode::setWorldAABBReference(AxisAlignedBoundingBox* aabb)
	{
		mWorldAABBReference = aabb;
	}

	NodeUPtr SceneNode::create_(
		const string& name,
		const Transform& transform
		)
	{
		NodeUPtr node = NodeUPtr(new SceneNode(
			mNodeChain, name, transform
			));
		return node;
	}

	CLAIRE_NAMESPACE_END
}