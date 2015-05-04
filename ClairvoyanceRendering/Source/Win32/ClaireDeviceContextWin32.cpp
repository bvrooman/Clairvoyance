#include "ClaireDeviceContextWin32.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	DeviceContextWin32::DeviceContextWin32(HDC hdc)
		: mHDC(hdc)
	{

	}

	DeviceContextWin32::~DeviceContextWin32(void)
	{

	}

	CLAIRE_NAMESPACE_END
}