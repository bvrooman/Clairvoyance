namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	inline HeapArea::HeapArea(const size_t size)
	{
		mByteArray = std::make_unique<byte[]>(size);
		byte* heap = mByteArray.get();
		mStart = heap;
		mEnd = heap + size;
	}

	inline HeapArea::~HeapArea(void)
	{
	}

	inline void* HeapArea::getStart(void) const
	{
		return mStart;
	}

	inline void* HeapArea::getEnd(void) const
	{
		return mEnd;
	}

	CLAIRE_NAMESPACE_END
}

