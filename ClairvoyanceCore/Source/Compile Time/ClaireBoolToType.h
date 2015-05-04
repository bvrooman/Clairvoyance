#ifndef CLAIRE_BOOL_TO_TYPE_H
#define CLAIRE_BOOL_TO_TYPE_H

namespace Claire
{
	template<bool C>
	struct BoolToType
	{
		enum { value = C };
		typedef bool value_type;

		typedef BoolToType<C> type;
	};

	typedef BoolToType<true> TrueType;
	typedef BoolToType<false> FalseType;
}

#endif