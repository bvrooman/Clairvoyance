#ifndef CLAIRE_NODE_CHAIN_TRANSFORM_COMPONENT_H
#define CLAIRE_NODE_CHAIN_TRANSFORM_COMPONENT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireINodeChainComponent.h"

#include "ClaireFlatNode.h"
#include "ClaireTransform.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Node;

	class NodeChainTransformComponent
		: public INodeChainComponent
	{
	private:
		static const size_t CHAIN_SIZE = MAX_NODE_CHAIN_SIZE;

	public:
		NodeChainTransformComponent(void);

		void addNode(Node* node) CLAIRE_OVERRIDE;
		void update(NodeHandle handle, FlatNode node) CLAIRE_OVERRIDE;

	private:
		inline void calculateDerivedTransform(NodeHandle handle, FlatNode node);

	private:
		NodeHandle mDirtyNode;
		bool mDirty;

		std::array<Transform, CHAIN_SIZE> mLocalTransforms;
		std::array<Transform, CHAIN_SIZE> mCachedLocalTransforms;
		std::array<Transform, CHAIN_SIZE> mDerivedTransforms;
	};

	CLAIRE_NAMESPACE_END
}

#endif