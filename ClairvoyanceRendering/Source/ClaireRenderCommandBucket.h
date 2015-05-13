#ifndef CLAIRE_RENDER_COMMAND_BUCKET_H
#define CLAIRE_RENDER_COMMAND_BUCKET_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireRenderCommand.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	template <typename T>
	class RenderCommandBucket
	{
		typedef T Key;

	public:
		RenderCommandBucket(size_t size);
		~RenderCommandBucket(void) = default;

		template <typename RenderCommand>
		RenderCommand& addCommand(Key key, size_t auxiliaryMemorySize);

		template <typename RenderCommand>
		RenderCommand& appendCommand(RenderCommand* command, size_t auxiliaryMemorySize);

		void sort(void);

		void submit(void);

	private:
		void submitRenderCommandPacket(const RenderCommandPacket packet);

	private:
		Key* mKeys;
		RenderCommandPacket* mPackets;

		size_t mCurrentIndex = 0;
	};

	CLAIRE_NAMESPACE_END
}

#include "ClaireRenderCommandBucket.inl"

#endif