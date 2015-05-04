#include "ClaireFreelist.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	Freelist::Freelist(void)
		: mNext(nullptr)
	{
	}

	Freelist::Freelist(const void* start, const void* end, size_t elementSize, size_t alignment, size_t offset)
		: mNext(nullptr)
	{
		union
		{
			void* asRaw;
			byte* asByte;
			Freelist* asFreelist;
		};

		asRaw = (void*)start;
		const size_t numElements = ((byte*)end - asByte) / elementSize;

		Freelist* runner = this;
		for(size_t i = 0; i < numElements; i++)
		{
			runner->mNext = asFreelist;
			runner = runner->mNext;

			asByte += elementSize;
		}
		runner->mNext = nullptr;
	}

	void* Freelist::getBlock(void)
	{
		if(mNext == nullptr)
		{
			return nullptr;	
		}

		Freelist* head = mNext;
		mNext = head->mNext;

		return head;
	}

	void Freelist::returnBlock(void* ptr)
	{
		Freelist* head = static_cast<Freelist*>(ptr);
		head->mNext = mNext;
		mNext = head;
	}

	CLAIRE_NAMESPACE_END
}