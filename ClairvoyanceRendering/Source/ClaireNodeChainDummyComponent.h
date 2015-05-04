#ifndef CLAIRE_NODE_CHAIN_DUMMY_COMPONENT_H
#define CLAIRE_NODE_CHAIN_DUMMY_COMPONENT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireINodeChainComponent.h"
#include "ClaireNode.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT NodeChainDummyComponent
		: public INodeChainComponent
	{
	private:
		static const size_t CHAIN_SIZE = MAX_NODE_CHAIN_SIZE;

	public:
		NodeChainDummyComponent(void) {}

		void addNode(Node* node) CLAIRE_OVERRIDE
		{
			NodeHandle handle = node->getNodeHandle();
			mStrings[handle] = node->getName();
		}
		void update(NodeHandle handle, FlatNode node) CLAIRE_OVERRIDE
		{
			std::cout << mStrings[handle] << "\n";
		}

	private:
		std::array<string, CHAIN_SIZE> mStrings;
	};

	CLAIRE_NAMESPACE_END
}

#endif