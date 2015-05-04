#ifndef CLAIRE_PIXEL_FORMAT_H
#define CLAIRE_PIXEL_FORMAT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT PixelFormat
		//: public GeneralAllocatedObject
	{
	public:
		PixelFormat(ushort red, ushort blue, ushort green, ushort alpha);
		virtual ~PixelFormat(void);
		
		ushort getRedBits(void) const { return mRedBits; }
		ushort getBlueBits(void) const { return mBlueBits; }
		ushort getGreenBits(void) const { return mGreenBits; }
		ushort getAlphaBits(void) const { return mAlphaBits; }
		ushort getColourDepth(void) const { return mRedBits + mBlueBits + mGreenBits + mAlphaBits; }

	protected:
		ushort mRedBits;
		ushort mBlueBits;
		ushort mGreenBits;
		ushort mAlphaBits;
	};

	typedef std::unique_ptr<PixelFormat> PixelFormatUPtr;

	CLAIRE_NAMESPACE_END
}

#endif