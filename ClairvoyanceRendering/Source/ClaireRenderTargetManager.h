#ifndef CLAIRE_RENDER_TARGET_MANAGER_H
#define CLAIRE_RENDER_TARGET_MANAGER_H

#include "ClaireRenderingPrerequisites.h"

#include "Idiom\ClaireManager.h"
#include "ClaireSTLContainers.h"
#include "ClaireRenderTarget.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT RenderTargetManager
	{
	public:
		RenderTargetManager(void) = default;
		~RenderTargetManager(void) = default;

		void attachRenderTarget(RenderTargetUPtr renderTarget);
		RenderTargetUPtr detachRenderTarget(const string& name);
		
		RenderTarget* getRenderTarget(const string& name);

		void updateAllRenderTargets(void);
		void swapAllRenderTargetBuffers(void);

	private:
		typedef OwningManager<RenderTarget, string> RenderTargetManagerImpl;
		RenderTargetManagerImpl mManagerImpl;

		typedef vector<RenderTarget*> RenderTargetVector;
		RenderTargetVector mRenderTargetVector;
	};

	CLAIRE_NAMESPACE_END
}

#endif