#ifndef CLAIRE_HEAP_AREA_H
#define CLAIRE_HEAP_AREA_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class HeapArea
	{
	public:
		inline explicit HeapArea(const size_t size);
		inline ~HeapArea(void);

		inline void* getStart(void) const;
		inline void* getEnd(void) const;

	private:
		void* mStart = nullptr;
		void* mEnd = nullptr;

		typedef std::unique_ptr<byte[]> ByteArrayUPtr;
		ByteArrayUPtr mByteArray = nullptr;
	};

	typedef std::unique_ptr<HeapArea> HeapAreaUPtr;

	CLAIRE_NAMESPACE_END
}

#include "ClaireHeapArea.inl"

#endif