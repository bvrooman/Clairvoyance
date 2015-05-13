#include "ClaireRenderTarget.h"

#include "ClaireViewport.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderTarget::RenderTarget(string name, size_t width, size_t height)
		: mName(std::move(name))
		, mWidth(width)
		, mHeight(height)
	{
		mPixelFormat = std::make_unique<PixelFormat>(
			8,	// Red 
			8,	// Green
			8,	// Blue
			8	// Alpha
			);
	}

	void RenderTarget::update(void)
	{
		updateViewports();
	}
	
	Viewport* RenderTarget::createViewport(
		Camera* camera,
		int zIndex,
		Colour backgroundColour,
		real left, real top,
		real width, real height
		)
	{
		Viewport* viewport = mViewportManager.create<Viewport>(
			zIndex,
			camera, zIndex, this, backgroundColour, left, top, width, height
			);

		mViewportVector.push_back(viewport);

		return viewport;
	}

	void RenderTarget::updateViewports(void)
	{
		for(auto&& viewport : mViewportVector)
		{
			viewport->update();
		}
	}

	CLAIRE_NAMESPACE_END
}