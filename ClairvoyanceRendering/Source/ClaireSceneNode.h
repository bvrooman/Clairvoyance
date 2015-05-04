#ifndef CLAIRE_SCENE_NODE_H
#define CLAIRE_SCENE_NODE_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireNode.h"

#include "ClaireAxisAlignedBoundingBox.h"
#include "ClaireNodeChain.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class SceneObject;

	class CLAIRE_RENDERING_EXPORT SceneNode
		: public Node
	{
	public:
		SceneNode(
			const string& name,
			const Transform& transform = Transform()
			);
		SceneNode(
			const Transform& transform = Transform()
			);
		~SceneNode(void);

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
		void setup(void);

		void update_(void) CLAIRE_OVERRIDE;

		void updateSceneObjectAABB(void);

		SceneNode(
			NodeChainSPtr nodeChain,
			const string& name,
			const Transform& transform = Transform()
			);
		SceneNode(
			NodeChainSPtr nodeChain,
			const Transform& transform = Transform()
			);

		NodeUPtr create_(
			const string& name,
			const Transform& transform
			) CLAIRE_OVERRIDE;

	private:
		typedef map<string, SceneObject*> SceneObjectMap;
		SceneObjectMap mSceneObjectMap;

		AxisAlignedBoundingBox* mSceneObjectAABBReference;
		AxisAlignedBoundingBox* mWorldAABBReference;

		static NameGenerator sNameGenerator;
	};
		

	CLAIRE_NAMESPACE_END
}

#endif