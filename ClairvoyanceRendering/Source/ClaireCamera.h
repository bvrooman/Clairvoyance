#ifndef CLAIRE_CAMERA_H
#define CLAIRE_CAMERA_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireSceneObject.h"

#include "ClaireViewFrustum.h"
#include "ClaireRadian.h"
#include "ClaireTransform.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Scene;
	class Viewport;

	class CLAIRE_RENDERING_EXPORT Camera
		: public SceneObject
	{
		CLAIRE_MOVABLE_ONLY(Camera)

	public:
		Camera(const string& name, Scene* Scene);
		~Camera(void) = default;

		void renderScene(Viewport* viewport);

		void setNearDistance(real nearDistance);
		void setFarDistance(real farDistance);
		void setAspectRatio(real aspectRatio);
		void setFieldOfView(Radian fieldOfView);

	private:
		void buildProjectionMatrix(void);
		void buildViewMatrix(void);

		void calculateLocalAABB(void) CLAIRE_OVERRIDE;
		
	private:
		Scene* mScene = nullptr;

		ViewFrustum mViewFrustum;

		Transform mCachedTransform;
	};

	typedef std::unique_ptr<Camera> CameraUPtr;

	CLAIRE_NAMESPACE_END
}

#endif