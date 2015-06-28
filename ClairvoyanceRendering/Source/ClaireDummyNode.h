#ifndef CLAIRE_DUMMY_NODE_H
#define CLAIRE_DUMMY_NODE_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireNode.h"

#include "ClaireNameGenerator.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT DummyNode
		: public Node
	{
	public:
		DummyNode(
			const string& name
			);
		DummyNode(
			const Transform& transform = Transform()
			);
		DummyNode(
			const string& name,
			const Transform& transform
			);
		~DummyNode(void) = default;

	private:
		// Inherit Node ctors
		using Node::Node;
		
		NodeUPtr create_(
			const string& name,
			const Transform& transform
			) CLAIRE_OVERRIDE;

		string generateName(void) CLAIRE_OVERRIDE
		{
			return sNameGenerator.generate();
		}

	private:
		static NameGenerator sNameGenerator;
	};

	CLAIRE_NAMESPACE_END
}

#endif