#include "Win32\ClairePluginGLWin32.h"

#include "ClaireRenderRoot.h"
#include "ClaireScene.h"
#include "ClaireCamera.h"
#include "ClaireNode.h"
#include "ClaireDummyNode.h"
#include "Mesh\ClaireMeshManager.h"
#include "Mesh\ClaireMesh.h"
#include "Mesh\ClaireSubMesh.h"
#include "ClaireEntity.h"

#include "ClaireRenderCommandBucket.h"
#include "ClaireRenderCommand.h"

#include "ClaireMatrix.h"
#include "ClaireVector.h"


using namespace Claire;
using namespace Claire::rendering;

#if _DEBUG
int main()
{
#else
int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
{
#endif
	PluginGLWin32 plugin;

	RenderRootUPtr root = std::make_unique<RenderRoot>();
	root->addPlugin(&plugin);
	root->installAllPlugins();

	root->setRenderSystem("RenderSystemGL");

	root->initialize();

	RenderSystem* rs = root->getActiveRenderSystem();
	RenderWindow* window;
	string name = "HelloWorld";

	root->createRenderWindow(name, 800, 600, false);
	window = rs->getRenderWindow(name);

	Scene* scene = root->getSceneManager()->createScene("defaultScene");
	Camera* camera = scene->createCamera("defaultCamera");

	Viewport* vp = window->createViewport(camera, 0, Colour::Blue, 0, 0, 0.5, 1);
	Viewport* vp2 = window->createViewport(camera, 1, Colour::Green, 0.5, 0, 0.5, 1);

	//root->getMeshManager()->loadResource("Bench", "bench.obj");
	//root->getMeshManager()->loadResource("Women", "Women.3ds");
	root->getMeshManager()->loadResource("Box", "box.fbx");
	Entity* e = scene->createEntity("HelloWorld", "Box");


	RenderCommandBucket<uint32_t> buffer(10);

	Mesh* m = e->getMesh();
	typedef vector<SubMesh*> SubMeshList;
	SubMeshList list = m->getSubMeshList();

	uint32_t key = 0;
	std::cout << list.size() << "\n";
	for_each(list.begin(), list.end(), [&](SubMesh* subMesh)
	{
		renderCommand::Draw& draw = buffer.addCommand<renderCommand::Draw>(key, 0);
		draw.renderObjectDescriptor = subMesh->getRenderObjectDescriptor();
		key++;
	});

	buffer.submit();

	root->startRendering();

	
	
#if _DEBUG
	system("PAUSE");
#endif
}