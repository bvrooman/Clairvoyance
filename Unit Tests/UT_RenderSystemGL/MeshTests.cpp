#include "gtest\gtest.h"

#include "Win32\ClairePluginGLWin32.h"
#include "ClaireRenderRoot.h"
#include "Mesh\ClaireMesh.h"
#include "Mesh\ClaireVertexDataFormat.h"

using namespace Claire::rendering;

TEST(Mesh, blah)
{
	PluginGLWin32 plugin;

	RenderRootUPtr root = std::make_unique<RenderRoot>();
	root->addPlugin(&plugin);
	root->installAllPlugins();
	root->setRenderSystem("RenderSystemGL");
	root->initialize();

	/*root->getMeshManager()->loadResource("Box", "box.fbx");
	Mesh* mesh = root->getMeshManager()->getMesh("Box");*/
}

TEST(VertexFormat, getVertexAttributeFromSemantic)
{
	VertexAttribute pos(VAS_POSITION, VAT_FLOAT, 3);
	VertexAttribute diffuseColour(IndexedVertexAttributeSemantic(VAS_COLOUR, 0), VAT_BYTE, 4);

	VertexFormat vertexFormat;
	vertexFormat.addVertexAttribute(pos);
	vertexFormat.addVertexAttribute(diffuseColour);

	const VertexAttribute* attributeResult1 = vertexFormat.getVertexAttributeFromSemantic(VAS_POSITION);
	const VertexAttribute* attributeResult2 = vertexFormat.getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic(VAS_COLOUR, 0));

	ASSERT_EQ(pos, *attributeResult1);
	ASSERT_EQ(diffuseColour, *attributeResult2);
}

TEST(VertexDataFormat, getVertexBufferFormatForSemantic)
{
	VertexAttribute pos(VAS_POSITION, VAT_FLOAT, 3);
	VertexAttribute diffuseColour(IndexedVertexAttributeSemantic(VAS_COLOUR, 0), VAT_BYTE, 4);

	VertexDataFormat vertexDataFormat;

	VertexFormat& vertexFormat = vertexDataFormat.getVertexFormat();
	vertexFormat.addVertexAttribute(pos);
	vertexFormat.addVertexAttribute(diffuseColour);

	VertexBufferFormat& bufferFormat1 = vertexDataFormat.createVertexBufferFormat(VertexBufferFormat::ST_INTERLEAVED);
	bufferFormat1.addVertexAttribute(pos);

	VertexBufferFormat& bufferFormat2 = vertexDataFormat.createVertexBufferFormat(VertexBufferFormat::ST_INTERLEAVED);
	bufferFormat2.addVertexAttribute(diffuseColour);

	VertexBufferFormat* bufferFormatResult1 = vertexDataFormat.getVertexBufferFormatForSemantic(VAS_POSITION);
	VertexBufferFormat* bufferFormatResult2 = vertexDataFormat.getVertexBufferFormatForSemantic(IndexedVertexAttributeSemantic(VAS_COLOUR, 0));

	ASSERT_EQ(&bufferFormat1, bufferFormatResult1);
	ASSERT_EQ(&bufferFormat2, bufferFormatResult2);
}
