#include "ClaireBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	BufferObject::BufferObject(BufferObjectManager* manager, EnumFlags usageSettings = 0)
		: mManager(manager)
		, mUsageSettingsFlags(usageSettings)
	{
	}

	void* BufferObject::lock(size_t offset, size_t length, EnumFlags lockSettings)
	{
		assert(!mIsLocked && "Buffer is already locked!");

		void* ptr = nullptr;

		if(length + offset > mBytes)
		{
			assert(false && "Lock out of bounds!");
		}

		mIsLocked = true;
		mLockOffset = offset;
		mLockLength = length;
		mLockSettings = lockSettings;

		ptr = lock_(offset, length, lockSettings);
		
		return ptr;
	}

	void* BufferObject::lock(EnumFlags lockSettings)
	{
		return lock(0, mBytes, lockSettings);
	}

	void BufferObject::unlock(void)
	{
		assert(mIsLocked && "Buffer is not locked!");

		unlock_();
		mIsLocked = false;
	}



	CLAIRE_NAMESPACE_END
}