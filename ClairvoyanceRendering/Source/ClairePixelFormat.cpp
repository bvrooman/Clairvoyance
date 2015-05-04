#include "ClairePixelFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	PixelFormat::PixelFormat(ushort red, ushort blue, ushort green, ushort alpha)
		: mRedBits(red)
		, mBlueBits(blue)
		, mGreenBits(green)
		, mAlphaBits(alpha)
	{
	}

	PixelFormat::~PixelFormat(void)
	{
	}

	CLAIRE_NAMESPACE_END
}