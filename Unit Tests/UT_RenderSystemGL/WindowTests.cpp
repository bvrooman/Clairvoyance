#include "gtest\gtest.h"

#include "ClaireRenderRoot.h"
#include "Win32\ClairePluginGLWin32.h"

using namespace Claire;
using namespace Claire::rendering;

namespace
{
	PluginGLWin32 plugin;
}

TEST(GL, CreateDestroyWindow)
{
	/*plugin.install();

	RenderRoot* root = RenderRoot::getInstance();
	root->setRenderSystem("RenderSystemGL");
	RenderSystem* rs = root->getActiveRenderSystem();

	RenderWindow* window;
	string name = "HelloWorld";

	rs->createRenderWindow(name, 800, 600, false);
	window = rs->getRenderWindow(name);
	ASSERT_TRUE(window != nullptr);

	rs->destroyRenderWindow(name);
	window = rs->getRenderWindow(name);
	ASSERT_TRUE(window == nullptr);

	plugin.uninstall();*/
}