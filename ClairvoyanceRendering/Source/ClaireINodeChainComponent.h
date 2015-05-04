#ifndef CLAIRE_I_NODE_CHAIN_COMPONENT_H
#define CLAIRE_I_NODE_CHAIN_COMPONENT_H

#include "ClaireRenderingPrerequisites.h"
#include "ClaireFlatNode.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Node;

	class CLAIRE_RENDERING_EXPORT INodeChainComponent
	{
	public:
		virtual void addNode(Node* node) CLAIRE_ABSTRACT;
		virtual void update(NodeHandle handle, FlatNode node) CLAIRE_ABSTRACT;
	};

	typedef std::unique_ptr<INodeChainComponent> NodeChainComponentUPtr;

	CLAIRE_NAMESPACE_END
}

#endif