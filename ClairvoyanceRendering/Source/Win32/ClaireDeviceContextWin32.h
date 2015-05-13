#ifndef CLAIRE_DEVICE_CONTEXT_WIN32_H
#define CLAIRE_DEVICE_CONTEXT_WIN32_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireDeviceContext.h"

#define NOMINMAX
#include <Windows.h>

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT DeviceContextWin32
		: public DeviceContext
	{
	public:
		DeviceContextWin32(HDC hdc);
		~DeviceContextWin32(void) = default;

		HDC getHDC(void) const { return mHDC; }

	protected:
		HDC mHDC;
	};

	CLAIRE_NAMESPACE_END
}

#endif