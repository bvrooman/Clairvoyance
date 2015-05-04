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
		//: public GeneralAllocatedObject
	{
	public:
		Viewport(
			Camera* camera, 
			int zIndex,
			RenderTarget* target,
			Colour backgroundColour = Colour::Black,
			real left = 0.0f, real top = 0.0f,
			real width = 1.0f, real height = 1.0f); 
		virtual ~Viewport();

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
		Camera* mCamera;
		RenderTarget* mRenderTarget;

		real mLeftPerc, mTopPerc, mWidthPerc, mHeightPerc;
		int mLeftDim, mTopDim, mWidthDim, mHeightDim;

		int mZIndex;

		Colour mBackgroundColour;
	};

	CLAIRE_NAMESPACE_END
}

#endif