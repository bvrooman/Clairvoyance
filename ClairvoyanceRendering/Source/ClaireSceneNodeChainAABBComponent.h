#ifndef CLAIRE_SCENE_NODE_CHAIN_AABB_COMPONENT_H
#define CLAIRE_SCENE_NODE_CHAIN_AABB_COMPONENT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireINodeChainComponent.h"
#include "ClaireAxisAlignedBoundingBox.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	/*
	NodeChain component for updating the AABBs for Scene Nodes.
	This component is meant to be updated in post-order traversal.
	Leaf nodes are updated before their parent nodes because the
	limits of an AABB must include their children.
	The last node to be updated in the update loop is the 
	root node, where the handle equals zero.
	*/
	class CLAIRE_RENDERING_EXPORT SceneNodeChainAABBComponent
		: public INodeChainComponent
	{
	private:
		static const size_t CHAIN_SIZE = MAX_NODE_CHAIN_SIZE;

	public:
		SceneNodeChainAABBComponent(void);
		
		void addNode(Node* node) CLAIRE_OVERRIDE;
		void update(NodeHandle handle, FlatNode node) CLAIRE_OVERRIDE;

	private:
		void updateAABBs(NodeHandle handle, FlatNode node);

	private:
		std::array<AxisAlignedBoundingBox, CHAIN_SIZE> mSceneObjectAABBs;
		std::array<AxisAlignedBoundingBox, CHAIN_SIZE> mWorldAABBs;
		std::array<bool, CHAIN_SIZE> mTaggedForClear;
	};

	CLAIRE_NAMESPACE_END
}

#endif