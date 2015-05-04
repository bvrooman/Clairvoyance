#include "ClaireRenderTargetManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderTargetManager::RenderTargetManager(void)
	{

	}

	RenderTargetManager::~RenderTargetManager(void)
	{

	}

	void RenderTargetManager::attachRenderTarget(RenderTargetUPtr renderTarget)
	{
		mRenderTargetVector.push_back(renderTarget.get());

		string name = renderTarget->getName();
		mManagerImpl.attach(name, renderTarget);
	}

	RenderTargetUPtr RenderTargetManager::detachRenderTarget(const string& name)
	{
		RenderTarget* target = mManagerImpl.get(name);
		mRenderTargetVector.erase(
			std::remove(mRenderTargetVector.begin(), mRenderTargetVector.end(), target),
			mRenderTargetVector.end()
			);

		return mManagerImpl.detach(name);
	}

	RenderTarget* RenderTargetManager::getRenderTarget(const string& name)
	{
		return mManagerImpl.get(name);
	}

	void RenderTargetManager::updateAllRenderTargets(void)
	{
		std::for_each(mRenderTargetVector.begin(), mRenderTargetVector.end(), [](RenderTarget* target)
		{
			target->update();
		});
	}

	void RenderTargetManager::swapAllRenderTargetBuffers(void)
	{
		std::for_each(mRenderTargetVector.begin(), mRenderTargetVector.end(), [](RenderTarget* target)
		{
			target->swapBuffers();
		});
	}

	CLAIRE_NAMESPACE_END
}