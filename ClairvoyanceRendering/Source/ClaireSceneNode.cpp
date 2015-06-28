#include "ClaireSceneNode.h"

#include "ClaireSceneObject.h"
#include "ClaireSceneNodeChainAABBComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	NameGenerator SceneNode::sNameGenerator("UnnamedSceneNode");

	SceneNode::SceneNode(
		const string& name
		)
		: SceneNode(
			name,
			Transform()
			)
	{
	}

	SceneNode::SceneNode(
		const Transform& transform
		)
		: SceneNode(
			generateName(),
			transform
			)
	{
	}

	SceneNode::SceneNode(
		const string& name,
		const Transform& transform
		)
		: Node(name, transform)
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

			for(auto&& type : mSceneObjectMap)
			{
				type.second->calculateWorldAABB();

				mSceneObjectAABBReference->merge(
					type.second->getWorldAABB()
					);
			}
		}

		for(auto&& child : mChildNodeVector)
		{
			SceneNode* sceneNode = static_cast<SceneNode*>(child);
			sceneNode->updateSceneObjectAABB();
		}
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
			generateName(),
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