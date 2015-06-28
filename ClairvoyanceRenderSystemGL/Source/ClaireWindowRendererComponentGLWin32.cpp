#include "ClaireWindowRendererComponentGLWin32.h"

#include "ClaireRenderWindow.h"
#include "ClaireWindowRendererSupport.h"
#include "Win32\ClaireWindowPlatformComponentWin32.h"
#include "Win32\ClaireRenderContextGLWin32.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	void WindowRendererComponentGLWin32::createRenderContext(void)
	{
		const DeviceContext* deviceContext = mParentRenderWindow->getPlatformComponent()->getDeviceContext();
		mRenderContext = std::make_unique<RenderContextGLWin32>(deviceContext);
	}


	CLAIRE_NAMESPACE_END
}