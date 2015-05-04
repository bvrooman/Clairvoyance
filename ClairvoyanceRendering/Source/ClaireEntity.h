#ifndef CLAIRE_ENTITY_H
#define CLAIRE_ENTITY_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireSceneObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Mesh;

	class CLAIRE_RENDERING_EXPORT Entity
		: public SceneObject
	{
	public:
		Entity(const string& name, Mesh* mesh);
		~Entity(void);

		void initialize(void);

		Mesh* getMesh(void) const { return mMesh; }

	private:
		void calculateLocalAABB(void) CLAIRE_OVERRIDE;

	private:
		Mesh* mMesh;

		bool mInitialized;
	};

	CLAIRE_NAMESPACE_END
}

#endif