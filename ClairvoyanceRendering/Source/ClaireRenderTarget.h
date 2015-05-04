#ifndef CLAIRE_RENDER_TARGET_H
#define CLAIRE_RENDER_TARGET_H

#include "ClaireRenderingPrerequisites.h"

#include "ClairePixelFormat.h"
#include "ClaireColour.h"
#include "Idiom\ClaireManager.h"
#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Viewport;
	class Camera;
	
	class CLAIRE_RENDERING_EXPORT RenderTarget
	{
	public:
		CLAIRE_MOVABLE_ONLY(RenderTarget)

		RenderTarget(string name, size_t width, size_t height);
		virtual ~RenderTarget(void);

		virtual void update(void);
		virtual void swapBuffers(void) {}

		string getName(void) const { return mName; }
		size_t getWidth(void) const { return mWidth; }
		size_t getHeight(void) const { return mHeight; }

		PixelFormat* getPixelFormat(void) const { return mPixelFormat.get(); }

		Viewport* createViewport(
			Camera* camera,
			int zIndex,
			Colour backgroundColour = Colour::Black,
			real left = 0.0f, real top = 0.0f,
			real width = 1.0f, real height = 1.0f
			);

	protected:
		void updateViewports(void);

	protected:
		string mName;

		size_t mWidth;
		size_t mHeight;
		PixelFormatUPtr mPixelFormat;

		typedef OwningManager<Viewport, int> ViewportManagerImpl;
		ViewportManagerImpl mViewportManager;

		typedef vector<Viewport*> ViewportVector;
		ViewportVector mViewportVector;
	};

	typedef std::unique_ptr<RenderTarget> RenderTargetUPtr;

	CLAIRE_NAMESPACE_END
}

#endif