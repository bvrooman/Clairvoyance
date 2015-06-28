#ifndef CLAIRE_SCENE_NODE_H
#define CLAIRE_SCENE_NODE_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireNode.h"

#include "ClaireAxisAlignedBoundingBox.h"
#include "ClaireNodeChain.h"
#include "ClaireNameGenerator.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class SceneObject;

	class CLAIRE_RENDERING_EXPORT SceneNode
		: public Node
	{
	public:
		SceneNode(
			const string& name
			);
		SceneNode(
			const Transform& transform = Transform()
			);
		SceneNode(
			const string& name,
			const Transform& transform
			);
		~SceneNode(void) = default;

		SceneNode* createChild(
			const string& name,
			const Transform& transform = Transform()
			);
		SceneNode* createChild(
			const Transform& transform = Transform()
			);

		void attachSceneObject(SceneObject* sceneObject);

		AxisAlignedBoundingBox getWorldAABB(void) const;

		void setSceneObjectAABBReference(AxisAlignedBoundingBox* aabb);
		void setWorldAABBReference(AxisAlignedBoundingBox* aabb);

	private:
		// Inherit Node ctors
		using Node::Node;

		void updateSceneObjectAABB(void);

		void update_(void) CLAIRE_OVERRIDE;

		NodeUPtr create_(
			const string& name,
			const Transform& transform
			) CLAIRE_OVERRIDE;

		string generateName(void) CLAIRE_OVERRIDE
		{
			return sNameGenerator.generate();
		}

	private:
		typedef map<string, SceneObject*> SceneObjectMap;
		SceneObjectMap mSceneObjectMap;

		AxisAlignedBoundingBox* mSceneObjectAABBReference = nullptr;
		AxisAlignedBoundingBox* mWorldAABBReference = nullptr;

	private:
		static NameGenerator sNameGenerator;
	};
		

	CLAIRE_NAMESPACE_END
}

#endif