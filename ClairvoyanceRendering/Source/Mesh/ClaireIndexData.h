#ifndef CLAIRE_INDEX_DATA_H
#define CLAIRE_INDEX_DATA_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class IndexBufferObject;

	class CLAIRE_RENDERING_EXPORT IndexData
	{
	public:
		IndexData(void) {}
		~IndexData(void) {}

		void setIndexBufferObject(IndexBufferObject* ibo) { mIndexBufferObject = ibo; }
		IndexBufferObject* getIndexBufferObject(void) const { return mIndexBufferObject; }

	private:
		IndexBufferObject* mIndexBufferObject = nullptr;
	};

	typedef std::unique_ptr<IndexData> IndexDataUPtr;

	CLAIRE_NAMESPACE_END
}

#endif