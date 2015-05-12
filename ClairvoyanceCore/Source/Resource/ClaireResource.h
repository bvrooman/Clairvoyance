#ifndef CLAIRE_RESOURCE_H
#define CLAIRE_RESOURCE_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class ResourceManager;

	class CLAIRE_CORE_EXPORT Resource
	{
	public:
		Resource(
			const string& name,
			const string& path,
			ResourceManager* manager
			);
		virtual ~Resource(void) = default;

		string getName(void) const { return mName; }
		size_t getSize(void) const { return mSize; }
		ResourceManager* getManager(void) const { return mManager; }

		void load(void);
		void unload(void);

	protected:
		virtual void preload_(void) CLAIRE_ABSTRACT;
		virtual void load_(void) CLAIRE_ABSTRACT;
		virtual void postload_(void) CLAIRE_ABSTRACT;
		virtual void unload_(void) CLAIRE_ABSTRACT;
		virtual void calculateSize(void) CLAIRE_ABSTRACT;

	protected:
		string mName;
		string mPath;
		ResourceManager* mManager;

		size_t mSize = 0;
		bool mLoaded = false;
	};

	typedef std::unique_ptr<Resource> ResourceUPtr;

	CLAIRE_NAMESPACE_END
}

#endif