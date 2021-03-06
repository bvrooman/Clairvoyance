#ifndef CLAIRE_BUFFER_OBJECT_H
#define CLAIRE_BUFFER_OBJECT_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	//typedef int BufferUsageSettingsFlags;
	//typedef int BufferLockSettingsFlags;

	class BufferObjectManager;

	class CLAIRE_RENDERING_EXPORT BufferObject
	{
	public:
		enum UsageSettings
		{
			// Static vs. Dynamic
			// Static buffers are rarely modified by the application.
			// Dynamic buffers are likely to be modified by the CPU.
			// By default, buffers are static.

			// Indicates the buffer will be dynamic.
			US_DYNAMIC		= 1 << 0,

			// Indicates the application will never read the contents of
			// the buffer.
			US_WRITE_ONLY	= 1 << 1,
		};

		enum LockSettings
		{
			// Read
			LS_READ			= 1 << 0,

			// Write
			LS_WRITE		= 1 << 1,

			// Discards the whole buffer
			LS_DISCARD		= 1 << 2,
		};

	public:
		BufferObject(BufferObjectManager* manager, EnumFlags usageSettings);
		virtual ~BufferObject(void) = default;

		// Lock a part of the buffer
		void* lock(size_t offset, size_t length, EnumFlags lockSettings);
		// Lock the whole buffer
		void* lock(EnumFlags lockSettings);

		void unlock(void);

	protected:
		virtual void* lock_(size_t offset, size_t length, EnumFlags lockSettings) CLAIRE_ABSTRACT;
		virtual void unlock_(void) CLAIRE_ABSTRACT;

		virtual void readData(size_t offset, size_t length, void* pDest) CLAIRE_ABSTRACT;
		virtual void writeData(size_t offset, size_t length, const void* pSrc, bool discardWholeBuffer) CLAIRE_ABSTRACT;

	protected:
		BufferObjectManager* mManager = nullptr;

		// Usage settings
		EnumFlags mUsageSettingsFlags = 0;

		// Size in bytes
		size_t mBytes = 0;

		// Where in the buffer the lock starts
		size_t mLockOffset = 0;

		// The size of the locked data
		size_t mLockLength = 0;

		// Lock settings
		EnumFlags mLockSettings = 0;

	private:
		bool mIsLocked = false;
	};

	typedef ushort BufferHandle;

	typedef std::unique_ptr<BufferObject> BufferObjectUPtr;

	CLAIRE_NAMESPACE_END
}

#endif