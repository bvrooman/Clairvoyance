#ifndef CLAIRE_NAME_GENERATOR_H
#define CLAIRE_NAME_GENERATOR_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT NameGenerator
	{
	public:
		NameGenerator(const string& prefix)
			: mPrefix(prefix)
			, mNext(1)
		{}

		string generate(void)
		{
			std::stringstream ss;
			ss << mPrefix << mNext++;
			return ss.str();
		}

		void reset(void)
		{
			mNext = 1;
		}

	private:
		string mPrefix;
		uint64_t mNext;
	};

	CLAIRE_NAMESPACE_END
}

#endif