#ifndef CLAIRE_RENDER_WINDOW_PLATFORM_DEFINITION_H
#define CLAIRE_RENDER_WINDOW_PLATFORM_DEFINITION_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireDeviceContext.h"
#include "ClairePixelFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderWindow;

	class CLAIRE_RENDERING_EXPORT WindowPlatformComponent
		//: public GeneralAllocatedObject
	{
	public:
		WindowPlatformComponent(RenderWindow* parentRenderWindow);
		virtual ~WindowPlatformComponent(void) = default;

		RenderWindow* getParentRenderWindow(void) const { return mParentRenderWindow; }

		virtual void create(void) CLAIRE_ABSTRACT;
		virtual void destroy(void) CLAIRE_ABSTRACT;

		string getDeviceName(void) const { return mDeviceName; }

		const DeviceContext* getDeviceContext(void) const { return mDeviceContext.get(); }

		size_t getLeft(void) const { return mLeft; }
		size_t getTop(void) const { return mTop; }
		size_t getColourDepth(void) const { return mColourDepth; }

		virtual void swapBuffers(void) CLAIRE_ABSTRACT;

	protected:
		// get parent RenderWindow's fullscreen value
		bool getFullscreen(void);

	protected:
		RenderWindow* mParentRenderWindow = nullptr;
		string mDeviceName;

		DeviceContextUPtr mDeviceContext = nullptr;

		PixelFormatUPtr mPixelFormat = nullptr;

		size_t mLeft = 0;
		size_t mTop = 0;
		size_t mColourDepth = 0; 
	};

	typedef std::unique_ptr<WindowPlatformComponent> WindowPlatformComponentUPtr;

	CLAIRE_NAMESPACE_END
}

#endif