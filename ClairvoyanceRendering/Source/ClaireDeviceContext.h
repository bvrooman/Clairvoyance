#ifndef CLAIRE_DEVICE_CONTEXT_H
#define CLAIRE_DEVICE_CONTEXT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT DeviceContext
		//: public GeneralAllocatedObject
	{
	public:
		DeviceContext(void) {}
		virtual ~DeviceContext(void) {}
	};

	typedef std::unique_ptr<DeviceContext> DeviceContextUPtr;

	CLAIRE_NAMESPACE_END
}

#endif