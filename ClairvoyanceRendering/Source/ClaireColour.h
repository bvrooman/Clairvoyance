#ifndef CLAIRE_COLOUR_H
#define CLAIRE_COLOUR_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT Colour
	{
	public:
		explicit Colour(
			float red = 1.0f,
			float green = 1.0f,
			float blue = 1.0f,
			float alpha = 1.0f
			)
			: r(red)
			, g(green)
			, b(blue)
			, a(alpha)
		{}

		inline float* ptr()
		{
			return &r;
		}

		inline const float* ptr() const
		{
			return &r;
		}

		inline friend std::ostream& operator <<
			(std::ostream& o, const Colour& colour)
		{
			o << "Colour( ";
			o << "R: " << colour.r << ", ";
			o << "G: " << colour.g << ", ";
			o << "B: " << colour.b << ", ";
			o << "A: " << colour.a;
			o << " )";
			return o;
		}

	public:
		float r, g, b, a;

	public:
		static const Colour Black;
		static const Colour White;
		static const Colour Red;
		static const Colour Green;
		static const Colour Blue;
	};

	CLAIRE_NAMESPACE_END
}

#endif