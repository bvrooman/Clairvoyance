#include "gtest\gtest.h"

#include "Buffers\ClaireBufferObject.h"

using namespace Claire::rendering;

class DummyBufferObject
	: public BufferObject
{
public:
	DummyBufferObject(EnumFlags usageSettings = 0)
		: BufferObject(nullptr, usageSettings)
	{
		if (!(mUsageSettingsFlags & US_DYNAMIC))
			std::cout << "STATIC\n";
		else
			std::cout << "DYNAMIC\n";
		if (mUsageSettingsFlags & US_WRITE_ONLY)
			std::cout << "WRITE ONLY\n";
		else
			std::cout << "READ WRITE\n";
	}

protected:
	void* lock_(size_t offset, size_t length, EnumFlags lockSettings) CLAIRE_OVERRIDE
	{
		return nullptr;
	}

	void unlock_(void) CLAIRE_OVERRIDE
	{}

	void readData(size_t offset, size_t length, void* pDest)
	{}

	void writeData(size_t offset, size_t length, const void* pSrc)
	{}

};

TEST(BufferUSageSettingsFlags, DummyBufferObject)
{
	/*EnumFlags flags = 0;
	flags |= BufferObject::US_DYNAMIC;
	flags |= BufferObject::US_WRITE_ONLY;

	DummyBufferObject dbo(flags);*/
}