//#include "gtest\gtest.h"
//
//#include "ClaireRenderRoot.h"
//
//#include "ClaireGLPlugin.h"
//
//using namespace Claire;
//using namespace Claire::rendering;
//
//namespace
//{
//	GLPlugin plugin;
//}

//TEST(GL, InstallUninstall)
//{
//	RenderRoot* root = RenderRoot::getInstance();
//	RenderSystem* rs;
//
//	plugin.install();
//	rs = root->getRenderSystem("RenderSystemGL");
//	ASSERT_TRUE(rs != nullptr);
//
//	plugin.uninstall();
//	rs = root->getRenderSystem("RenderSystemGL");
//	ASSERT_TRUE(rs == nullptr);
//}
//
//TEST(GL, SetRenderSystemToGL)
//{
//	RenderRoot* root = RenderRoot::getInstance();
//
//	plugin.install();
//	root->setRenderSystem("RenderSystemGL");
//	RenderSystem* system = root->getActiveRenderSystem();
//
//	ASSERT_EQ("RenderSystemGL", system->getName());
//
//	plugin.uninstall();
//}