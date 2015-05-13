#include "ClaireMeshManager.h"

#include "ClaireMesh.h"
#include "ClaireMeshSerializerAssimp.h"

#include "Buffers\ClaireVertexAttribute.h"
#include "Buffers\ClaireVertexFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	MeshManager::MeshManager(BufferObjectManager* bufferObjectManager)
		: mBufferObjectManager(bufferObjectManager)
	{
		mSerializerAdapter = std::make_unique<MeshSerializerAssimp>(this);

		VertexAttribute pos(VAS_POSITION, VAT_FLOAT, 3);
		VertexAttribute normal(VAS_NORMAL, VAT_FLOAT, 3);
		VertexAttribute tangent(VAS_TANGENT, VAT_FLOAT, 3);
		VertexAttribute diffuseColour(IndexedVertexAttributeSemantic(VAS_COLOUR, 0), VAT_BYTE, 4);
		VertexAttribute specularColour(IndexedVertexAttributeSemantic(VAS_COLOUR, 1), VAT_BYTE, 4);
		VertexAttribute textureCoord0(IndexedVertexAttributeSemantic(VAS_TEXTURE_COORDINATE, 0), VAT_USHORT, 2);
		VertexAttribute textureCoord1(IndexedVertexAttributeSemantic(VAS_TEXTURE_COORDINATE, 1), VAT_USHORT, 2);

		VertexFormat& vertexFormat = mPreferredVertexDataFormat.getVertexFormat();
		vertexFormat.addVertexAttribute(pos);
		vertexFormat.addVertexAttribute(normal);
		vertexFormat.addVertexAttribute(tangent);
		vertexFormat.addVertexAttribute(diffuseColour);
		vertexFormat.addVertexAttribute(specularColour);
		vertexFormat.addVertexAttribute(textureCoord0);
		vertexFormat.addVertexAttribute(textureCoord1);

		VertexBufferFormat& bufferFormat = mPreferredVertexDataFormat.createVertexBufferFormat(VertexBufferFormat::ST_INTERLEAVED);
		bufferFormat.addVertexAttribute(pos);
		bufferFormat.addVertexAttribute(normal);
		bufferFormat.addVertexAttribute(tangent);
		bufferFormat.addVertexAttribute(diffuseColour);
		bufferFormat.addVertexAttribute(specularColour);
		bufferFormat.addVertexAttribute(textureCoord0);
		bufferFormat.addVertexAttribute(textureCoord1);
	}

	Mesh* MeshManager::getMesh(const string& name) const
	{
		return (Mesh*)getResource(name);
	}

	Resource* MeshManager::createResource_(
		const string& name,
		const string& path
		)
	{
		return mManagerImpl.create<Mesh>(
			name,
			name, path, this
			);
	}

	CLAIRE_NAMESPACE_END
}