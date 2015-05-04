#include "ClaireMeshSerializerAssimp.h"

#include <assimp\Importer.hpp>

#include "Mesh\ClaireMesh.h"
#include "Mesh\ClaireMeshManager.h"
#include "Buffers\ClaireBufferObjectManager.h"
#include "Buffers\ClaireVertexAttribute.h"
#include "Buffers\ClaireVertexBufferFormat.h"

#include "Buffers\ClaireVertexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	MeshSerializerAssimp::MeshSerializerAssimp(MeshManager* meshManager)
		: mMeshManager(meshManager)
	{
		mBufferObjectManager = mMeshManager->getBufferObjectManager();
	}

	MeshSerializerAssimp::~MeshSerializerAssimp(void)
	{

	}

	void MeshSerializerAssimp::importMesh(const string& path, Mesh* dest)
	{
		Assimp::Importer importer;

		const aiScene* scene = nullptr;
		scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);

		if(!scene)
		{
			std::cout << "Unable to import mesh!\n";
			return;
		}

		processScene(scene, dest);
	}

	void MeshSerializerAssimp::processScene(const aiScene* scene, Mesh* dest)
	{
		for(size_t i = 0; i < scene->mNumMeshes; i++)
		{
			const struct aiMesh* mesh = scene->mMeshes[i];
			SubMesh* sm = dest->createSubMesh();
			readSubMesh(scene, mesh, sm);
		}
	}

	void MeshSerializerAssimp::readSubMesh(const aiScene* scene, const aiMesh* rawSubMesh, SubMesh* subMesh)
	{
		/*struct aiMaterial *mtl = scene->mMaterials[rawSubMesh->mMaterialIndex];
		aiString texPath;
		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath))
		{
			string materialName = string(texPath.data);
			subMesh->setMaterialName(materialName);
		}*/

		readIndices(rawSubMesh, subMesh);
		readVertexGeometry(rawSubMesh, subMesh);
	}

	void MeshSerializerAssimp::readIndices(const aiMesh* rawSubMesh, SubMesh* subMesh)
	{
		size_t icount = rawSubMesh->mNumFaces * 3;
		IndexBufferObject::IndexType indexType = IndexBufferObject::IT_32BIT;
		if(icount <= 65535)
		{
			indexType = IndexBufferObject::IT_16BIT;
		}
		if(icount <= 255)
		{
			indexType = IndexBufferObject::IT_8BIT;
		}

		IndexBufferObject* ibo = (IndexBufferObject*)mBufferObjectManager->createIndexBufferObject(
			indexType,
			icount,
			subMesh->getParentMesh()->getIndexBufferUsageSettingsFlags()
			);

		unsigned int* faceArray = (unsigned int*)operator new (icount * sizeof(unsigned int));
		size_t faceIndex = 0;

		for(size_t t = 0; t < rawSubMesh->mNumFaces; t++)
		{
			const struct aiFace* face = &rawSubMesh->mFaces[t];
			memcpy(&faceArray[faceIndex], face->mIndices, sizeof(unsigned int) * 3);
			faceIndex += 3;
		}

		switch(indexType)
		{
		case IndexBufferObject::IT_8BIT:
			{
				uint8_t* pIndexData = static_cast<uint8_t*>(
					ibo->lock(BufferObject::LS_DISCARD | BufferObject::LS_WRITE)
					);

				for(size_t i = 0; i < icount; i++)
				{
					pIndexData[i] = (uint8_t)faceArray[i];
				}
				ibo->unlock();
			}
			break;
		case IndexBufferObject::IT_16BIT:
			{
				uint16_t* pIndexData = static_cast<uint16_t*>(
					ibo->lock(BufferObject::LS_DISCARD | BufferObject::LS_WRITE)
					);
				for(size_t i = 0; i < icount; i++)
				{
					pIndexData[i] = (uint16_t)faceArray[i];
				}
				ibo->unlock();
			}
			break;

		case IndexBufferObject::IT_32BIT:
		default:
			{
				uint32_t* pIndexData = static_cast<uint32_t*>(
					ibo->lock(BufferObject::LS_DISCARD | BufferObject::LS_WRITE)
					);
				for(size_t i = 0; i < icount; i++)
				{
					pIndexData[i] = faceArray[i];
				}
				ibo->unlock();
			}
			break;
		}
		
		operator delete (faceArray);
		subMesh->getIndexData()->setIndexBufferObject(ibo);
	}

	void MeshSerializerAssimp::readVertexGeometry(const aiMesh* rawSubMesh, SubMesh* subMesh)
	{
		VertexDataFormat preferredVertexDataFormat = *mMeshManager->getPreferredVertexDataFormat();
		VertexFormat vertexFormat = preferredVertexDataFormat.getVertexFormat();

		VertexDataFormat vertexDataFormat;

		typedef list<IndexedVertexAttributeSemantic> SemanticList;
		SemanticList semantics;

		if(rawSubMesh->HasPositions() &&
			vertexFormat.hasSemantic(VAS_POSITION))
		{
			semantics.push_back(VAS_POSITION);
		}
		if(rawSubMesh->HasNormals() && 
			vertexFormat.hasSemantic(VAS_NORMAL))
		{
			semantics.push_back(VAS_NORMAL);
		}
		if(rawSubMesh->HasTangentsAndBitangents() &&
			vertexFormat.hasSemantic(VAS_TANGENT)
			)
		{
			semantics.push_back(VAS_TANGENT);
		}
		if(rawSubMesh->HasTangentsAndBitangents() &&
			vertexFormat.hasSemantic(VAS_BITANGENT)
			)
		{
			semantics.push_back(VAS_BITANGENT);
		}
		for(ushort i = 0; i < SubMesh::MAX_TEXTURE_COORDINATES; i++)
		{
			IndexedVertexAttributeSemantic semantic(VAS_TEXTURE_COORDINATE, i);
			if(rawSubMesh->HasTextureCoords(i) &&
				vertexFormat.hasSemantic(semantic))
			{
				semantics.push_back(semantic);
			}
		}
		for(ushort i = 0; i < SubMesh::MAX_COLOUR_SETS; i++)
		{
			IndexedVertexAttributeSemantic semantic(VAS_COLOUR, i);
			if(rawSubMesh->HasVertexColors(i) &&
				vertexFormat.hasSemantic(semantic))
			{
				semantics.push_back(semantic);
			}
		}

		typedef set<VertexBufferFormat*> VertexBufferFormatSet;
		VertexBufferFormatSet preferredBufferFormatSet;
		for_each(semantics.begin(), semantics.end(), [&](IndexedVertexAttributeSemantic semantic)
		{
			VertexBufferFormat* preferredBufferFormat = 
				preferredVertexDataFormat.getVertexBufferFormatForSemantic(semantic);

			if(preferredBufferFormat)
			{
				// Store all the unique buffer formats
				preferredBufferFormatSet.insert(preferredBufferFormat);
			}
		});

		VertexData* vertexData = subMesh->getVertexData();
		size_t vcount = rawSubMesh->mNumVertices;

		for_each(preferredBufferFormatSet.begin(), preferredBufferFormatSet.end(), [&](VertexBufferFormat* preferredBufferFormat)
		{
			VertexBufferFormatUPtr bufferFormat =
				std::make_unique<VertexBufferFormat>(preferredBufferFormat->getSequenceType());
			for_each(semantics.begin(), semantics.end(), [&](IndexedVertexAttributeSemantic semantic)
			{
				bufferFormat->addVertexAttribute(
					*preferredBufferFormat->getVertexAttributeFromSemantic(semantic)
					);
			});

			VertexFormat vertexFormatPiece =
				bufferFormat->getVertexFormatPiece();

			// Create the corresponding VBO
			VertexBufferObject* vbo = (VertexBufferObject*)mBufferObjectManager->createVertexBufferObject(
				vertexFormatPiece.getVertexSize(),
				vcount,
				subMesh->getParentMesh()->getVertexBufferUsageSettingsFlags()
				);

			readVertexGeometryBuffer(rawSubMesh, bufferFormat.get(), vbo);

			// Add each vertex buffer format to the submesh's vertex data
			VertexData::VertexBufferObjectHandle handle =
				vertexData->addVertexBufferFormat(std::move(bufferFormat));
			vertexData->bindVertexBuffer(handle, vbo);
		});
	}

	void MeshSerializerAssimp::readVertexGeometryBuffer(const aiMesh* rawSubMesh, VertexBufferFormat* format, VertexBufferObject* vbo)
	{
		switch(format->getSequenceType())
		{
		case VertexBufferFormat::ST_SEQUENTIAL:
			readVertexGeometryBufferSequential(rawSubMesh, format, vbo);
			break;
		
		case VertexBufferFormat::ST_INTERLEAVED:
		default:
			readVertexGeometryBufferInterleaved(rawSubMesh, format, vbo);
			break;
		}
	}

	void MeshSerializerAssimp::readVertexGeometryBufferSequential(const aiMesh* rawSubMesh, VertexBufferFormat* format, VertexBufferObject* vbo)
	{
		size_t vcount = rawSubMesh->mNumVertices;
		VertexFormat vertexFormat = format->getVertexFormatPiece();
		VertexFormat::VertexAttributeVector attributes = vertexFormat.getVertexAttributeVector();

		void* pVertexData = vbo->lock(BufferObject::LS_DISCARD | BufferObject::LS_WRITE);

		for_each(attributes.begin(), attributes.end(), [&](VertexAttribute attribute)
		{
			size_t bytes = attribute.getSize() * vcount;
			IndexedVertexAttributeSemantic indexedSemantic = attribute.getSemantic();
			switch(indexedSemantic.semantic)
			{
			case VAS_POSITION:
				if(rawSubMesh->HasPositions())
				{
					memcpy(pVertexData, rawSubMesh->mVertices, bytes);
				}
				break;
			case VAS_NORMAL:
				if(rawSubMesh->HasNormals())
				{
					memcpy(pVertexData, rawSubMesh->mNormals, bytes);
				}
				break;
			case VAS_TANGENT:
				if(rawSubMesh->HasTangentsAndBitangents())
				{
					memcpy(pVertexData, rawSubMesh->mTangents, bytes);
				}
				break;
			case VAS_BITANGENT:
				if(rawSubMesh->HasTangentsAndBitangents())
				{
					memcpy(pVertexData, rawSubMesh->mBitangents, bytes);
				}
				break;
			case VAS_TEXTURE_COORDINATE:
				if(rawSubMesh->HasTextureCoords(indexedSemantic.index))
				{
					memcpy(pVertexData, rawSubMesh->mTextureCoords[indexedSemantic.index], bytes);
				}
				break;
			case VAS_COLOUR:
				if(rawSubMesh->HasTextureCoords(indexedSemantic.index))
				{
					memcpy(pVertexData, rawSubMesh->mColors[indexedSemantic.index], bytes);
				}
				break;
			default:
				break;
			}

			// Increment the vertex data
			pVertexData = static_cast<byte*>(pVertexData) + bytes;
		});

		vbo->unlock();
	}

	void MeshSerializerAssimp::readVertexGeometryBufferInterleaved(const aiMesh* rawSubMesh, VertexBufferFormat* format, VertexBufferObject* vbo)
	{
		size_t vcount = rawSubMesh->mNumVertices;
		VertexFormat vertexFormat = format->getVertexFormatPiece();
		VertexFormat::VertexAttributeVector attributes = vertexFormat.getVertexAttributeVector();

		void* pVertexData = vbo->lock(BufferObject::LS_DISCARD | BufferObject::LS_WRITE);

		for(size_t i = 0; i < vcount; i++)
		{
			for_each(attributes.begin(), attributes.end(), [&](VertexAttribute attribute)
			{
				size_t bytes = attribute.getSize();
				IndexedVertexAttributeSemantic indexedSemantic = attribute.getSemantic();
			
				switch(indexedSemantic.semantic)
				{
				case VAS_POSITION:
					if(rawSubMesh->HasPositions())
					{
						memcpy(pVertexData, &rawSubMesh->mVertices[i], bytes);
					}
					break;
				case VAS_NORMAL:
					if(rawSubMesh->HasNormals())
					{
						memcpy(pVertexData, &rawSubMesh->mNormals[i], bytes);
					}
					break;
				case VAS_TANGENT:
					if(rawSubMesh->HasTangentsAndBitangents())
					{
						memcpy(pVertexData, &rawSubMesh->mTangents[i], bytes);
					}
					break;
				case VAS_BITANGENT:
					if(rawSubMesh->HasTangentsAndBitangents())
					{
						memcpy(pVertexData, &rawSubMesh->mBitangents[i], bytes);
					}
					break;
				case VAS_TEXTURE_COORDINATE:
					if(rawSubMesh->HasTextureCoords(indexedSemantic.index))
					{
						memcpy(pVertexData, &rawSubMesh->mTextureCoords[indexedSemantic.index][i], bytes);
					}
					break;
				case VAS_COLOUR:
					if(rawSubMesh->HasTextureCoords(indexedSemantic.index))
					{
						memcpy(pVertexData, &rawSubMesh->mColors[indexedSemantic.index][i], bytes);
					}
					break;
				default:
					break;
				}

				// Increment the vertex data
				pVertexData = static_cast<byte*>(pVertexData) + bytes;
			});
		}

		vbo->unlock();
	}

	CLAIRE_NAMESPACE_END
};