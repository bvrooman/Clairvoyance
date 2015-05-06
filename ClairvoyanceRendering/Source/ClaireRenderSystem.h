#ifndef CLAIRE_RENDER_SYSTEM_H
#define CLAIRE_RENDER_SYSTEM_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireRenderWindow.h"

#include "ClaireRenderTargetManager.h"
#include "ClaireRenderWindowManager.h"

#include "Buffers\ClaireBufferObjectManager.h"

#include "ClaireColour.h"

#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class WindowPlatformSupport;
	class WindowRendererSupport;

	class Viewport;

	class CLAIRE_RENDERING_EXPORT RenderSystem
		//: public GeneralAllocatedObject
	{
		CLAIRE_MOVABLE_ONLY(RenderSystem)

	public:
		RenderSystem(
			const string& name,
			const WindowPlatformSupport* windowPlatformSupport,
			const WindowRendererSupport* windowRendererSupport
			);
		virtual ~RenderSystem(void);

		virtual void initialize(void);

		virtual void startup(void);
		virtual void shutdown(void);

		virtual void render(void) CLAIRE_ABSTRACT;
		virtual void setViewport(Viewport* viewport) CLAIRE_ABSTRACT;
		virtual void clearFrameBuffer(const Colour& colour = Colour::Black) CLAIRE_ABSTRACT;

		void update(void);

		RenderWindow* createRenderWindow(const string& name, size_t width, size_t height, bool fullscreen);
		void destroyRenderWindow(const string& name);
		RenderWindow* getRenderWindow(const string& name) const;

		string getName(void) const { return mName; }

		BufferObjectManager* getBufferObjectManager(void) const { return mBufferObjectManager.get(); }

	protected:
		string mName;

		bool mInitialized = false;

		BufferObectManagerUPtr mBufferObjectManager;

		RenderTargetManager mRenderTargetManager;
		RenderWindowManager mRenderWindowManager;

		Viewport* mActiveViewport = nullptr;
	};

	typedef std::unique_ptr<RenderSystem> RenderSystemUPtr;

	CLAIRE_NAMESPACE_END
}

#endif