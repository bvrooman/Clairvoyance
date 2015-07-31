#ifndef CLAIRE_FREELIST_H
#define CLAIRE_FREELIST_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT Freelist
	{
	public:
		Freelist(void);
		Freelist(const void* start, const void* end, size_t elementSize);

		void* getBlock(void);
		void returnBlock(void* ptr);

	private:
		Freelist* mNext = nullptr;
	};

	CLAIRE_NAMESPACE_END
}

#endif