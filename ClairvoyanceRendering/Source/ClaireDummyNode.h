#ifndef CLAIRE_DUMMY_NODE_H
#define CLAIRE_DUMMY_NODE_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireNode.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT DummyNode
		: public Node
	{
	public:
		DummyNode(
			const string& name,
			const Transform& transform = Transform()
			);
		DummyNode(
			const Transform& transform = Transform()
			);
		~DummyNode(void);

	private:
		DummyNode(
			NodeChainSPtr nodeChain,
			const string& name,
			const Transform& transform = Transform()
			);
		DummyNode(
			NodeChainSPtr nodeChain,
			const Transform& transform = Transform()
			);

		NodeUPtr create_(
			const string& name,
			const Transform& transform
			) CLAIRE_OVERRIDE;

		void setup(void);
	};

	CLAIRE_NAMESPACE_END
}

#endif