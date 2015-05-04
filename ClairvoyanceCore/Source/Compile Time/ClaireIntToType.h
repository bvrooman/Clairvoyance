#ifndef CLAIRE_INT_TO_TYPE_H
#define CLAIRE_INT_TO_TYPE_H

namespace Claire
{
	template<int I>
	struct IntToType
	{
		enum { value = I };
		typedef int value_type;

		typedef IntToType<I> type;
		typedef IntToType<I + 1> next;
		typedef IntToType<I - 1> previous;
	};
}

#endif