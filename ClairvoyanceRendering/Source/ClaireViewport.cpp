#include "ClaireViewport.h"

#include "ClaireCamera.h"
#include "ClaireRenderTarget.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

		Viewport::Viewport(
			Camera* camera,
			int zIndex,
			RenderTarget* target,
			Colour backgroundColour,
			real left, real top,
			real width, real height)
		: mCamera(camera)
		, mZIndex(zIndex)
		, mRenderTarget(target)
		, mBackgroundColour(backgroundColour)
		, mLeftPerc(left)
		, mTopPerc(top)
		, mWidthPerc(width)
		, mHeightPerc(height)
	{
		updateDimensions();
	}

	Viewport::~Viewport(void)
	{
		
	}

	void Viewport::updateDimensions(void)
	{
		size_t width = mRenderTarget->getWidth();
		size_t height = mRenderTarget->getHeight();

		mLeftDim = (size_t)(mLeftPerc * width);
		mTopDim = (size_t)(mTopPerc * height);
		mWidthDim = (size_t)(mWidthPerc * width);
		mHeightDim = (size_t)(mHeightPerc * height);

		if(mCamera)
		{
			mCamera->setAspectRatio((real)mWidthDim / (real)mHeightDim);
		}
	}

	void Viewport::update(void)
	{
		if(mCamera)
		{
			mCamera->renderScene(this);
		}
	}

	CLAIRE_NAMESPACE_END
}