#ifndef CLAIRE_VIEWPORT_H
#define CLAIRE_VIEWPORT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireColour.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Camera;
	class RenderTarget;

	class CLAIRE_RENDERING_EXPORT Viewport
	{
	public:
		Viewport(
			Camera* camera, 
			int zIndex,
			RenderTarget* target,
			Colour backgroundColour = Colour::Black,
			real left = 0.0f, real top = 0.0f,
			real width = 1.0f, real height = 1.0f); 
		virtual ~Viewport(void) = default;

		virtual void update(void);

		RenderTarget* getRenderTarget(void) const { return mRenderTarget; }

		int getLeftDim(void) const { return mLeftDim; }
		int getTopDim(void) const { return mTopDim; }
		int getWidthDim(void) const { return mWidthDim; }
		int getHeightDim(void) const { return mHeightDim; }

		Colour getBackgroundColour(void) const { return mBackgroundColour; }

	protected:
		void updateDimensions(void);

	protected:
		Camera* mCamera = nullptr;
		RenderTarget* mRenderTarget = nullptr;

		real mLeftPerc = 1.0f;
		real mTopPerc = 1.0f; 
		real mWidthPerc = 1.0f;
		real mHeightPerc = 1.0f;

		int mLeftDim = 0;
		int mTopDim = 0;
		int mWidthDim = 0;
		int mHeightDim = 0;

		int mZIndex = 0;

		Colour mBackgroundColour = Colour::Black;
	};

	CLAIRE_NAMESPACE_END
}

#endif