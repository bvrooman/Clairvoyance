#ifndef CLAIRE_SCENE_OBJECT_FACTORY_H
#define CLAIRE_SCENE_OBJECT_FACTORY_H

#include "ClaireRenderingPrerequisites.h"

#include "Idiom\ClaireManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class SceneObject;

	class CLAIRE_RENDERING_EXPORT SceneObjectFactory
	{
		CLAIRE_MOVABLE_ONLY(SceneObjectFactory)

	public:
		typedef map<string, string> ParamMap;

	public:
		SceneObjectFactory(void) = default;
		virtual ~SceneObjectFactory(void) = default;

		SceneObject* createSceneObject(const string& name, const ParamMap* paramMap = 0);

	protected:
		virtual SceneObject* createSceneObject_(const string& name, const ParamMap* paramMap) CLAIRE_ABSTRACT;
	
	protected:
		typedef OwningManager<SceneObject, string> SceneObjectManagerImpl;
		SceneObjectManagerImpl mManagerImpl;
	};

	typedef std::unique_ptr<SceneObjectFactory> SceneObjectFactoryUPtr;

	CLAIRE_NAMESPACE_END
}

#endif