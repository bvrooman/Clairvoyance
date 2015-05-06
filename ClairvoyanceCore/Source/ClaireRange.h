#ifndef CLAIRE_RANGE_H
#define CLAIRE_RANGE_H

namespace Claire
{
	template <typename It>
	class Range
	{
	public:
		typedef It iterator;

		Range() : _begin(), _end() {}
		Range(iterator begin, iterator end) : mBegin(begin), mEnd(end) {}

		iterator begin() const { return mBegin; }
		iterator end() const { return mEnd; }

	private:
		iterator mBegin;
		iterator mEnd;
	};

	template <typename C>
	Range<typename C::iterator> range(C& c, size_t begin, size_t end)
	{
		return Range<typename C::iterator>(
			std::next(c.begin(), begin),
			std::next(c.begin(), end)
			);
	}

	template <typename C>
	Range<typename C::const_iterator> range(const C& c, size_t begin, size_t end)
	{
		return Range<typename C::const_iterator>(
			std::next(c.begin(), begin),
			std::next(c.begin(), end)
			);
	}
}

#endif