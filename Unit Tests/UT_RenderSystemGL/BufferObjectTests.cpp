#include "gtest\gtest.h"

#include "DummyBufferObject.h"

TEST(BufferUSageSettingsFlags, DummyBufferObject)
{
	EnumFlags flags = 0;
	flags |= BufferObject::US_DYNAMIC;
	flags |= BufferObject::US_WRITE_ONLY;

	DummyBufferObject dbo(flags);
}