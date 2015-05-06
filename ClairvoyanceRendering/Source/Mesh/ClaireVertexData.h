#ifndef CLAIRE_VERTEX_DATA_H
#define CLAIRE_VERTEX_DATA_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireSTLContainers.h"
#include "Buffers\ClaireVertexFormat.h"
#include "ClaireVertexDataFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class VertexBufferObject;
	class VertexBufferFormat;

	class CLAIRE_RENDERING_EXPORT VertexData
	{
		CLAIRE_NON_COPYABLE(VertexData)

	public:
		typedef uint8_t VertexBufferObjectHandle;
		static const VertexBufferObjectHandle INVALID_HANDLE = UINT8_MAX;

		typedef map<VertexBufferObjectHandle, VertexBufferObject*> VertexBufferObjectMap;
		typedef map<VertexBufferObjectHandle, VertexBufferFormatUPtr> VertexBufferFormatMap;
		
		typedef list<VertexBufferObjectHandle> VBOHandleList;

	public:
		VertexData(void);
		~VertexData(void);

		VertexBufferObjectHandle addVertexBufferFormat(VertexBufferFormatUPtr format);

		// Bind a vertex buffer to a VBO handle
		void bindVertexBuffer(VertexBufferObjectHandle handle, VertexBufferObject* vbo);
		
		VertexBufferFormat* getVertexBufferFormat(VertexBufferObjectHandle handle) const;
		VertexBufferObject* getVertexBufferObject(VertexBufferObjectHandle handle) const;

		VertexBufferObjectHandle getVBOHandleFromSemantic(IndexedVertexAttributeSemantic semantic);

	private:
		void bindVertexBufferFormat(VertexBufferObjectHandle handle, VertexBufferFormatUPtr format);

	private:
		VertexBufferObjectHandle mCurrentHandle = 0;

		VBOHandleList mVBOHandleList;
		VertexBufferObjectMap mVertexBufferObjectMap;
		VertexBufferFormatMap mVertexBufferFormatMap;
	};

	typedef std::unique_ptr<VertexData> VertexDataUPtr;

	CLAIRE_NAMESPACE_END
}

#endif