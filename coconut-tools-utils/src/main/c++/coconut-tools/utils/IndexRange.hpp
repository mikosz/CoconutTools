#ifndef COCONUT_TOOLS_UTILS_INDEXRANGE_HPP_
#define COCONUT_TOOLS_UTILS_INDEXRANGE_HPP_

#include <boost/operators.hpp>

namespace coconut_tools {
namespace utils {

class IndexRange {
public:

	class Iterator : public boost::bidirectional_iterator_helper<Iterator, const size_t> {
	public:

		Iterator() = default;

		explicit Iterator(size_t current) :
			current_(current)
		{
		}

		const size_t& operator*() const {
			return current_;
		}

		Iterator& operator++() {
			++current_;
			return *this;
		}

		Iterator& operator--() {
			--current_;
			return *this;
		}

		bool operator==(const Iterator& other) const {
			return current_== other.current_;
		}

	private:

		size_t current_;

	};

	class ReverseIterator : public boost::bidirectional_iterator_helper<ReverseIterator, const size_t> {
	public:

		ReverseIterator() = default;

		ReverseIterator(Iterator forward) :
			current_(*forward - 1)
		{
		}

		const size_t& operator*() const {
			return current_;
		}

		ReverseIterator& operator++() {
			--current_;
			return *this;
		}

		ReverseIterator& operator--() {
			++current_;
			return *this;
		}

		bool operator==(const ReverseIterator& other) const {
			return current_== other.current_;
		}

	private:

		size_t current_;

	};

	using iterator = Iterator;
	using const_iterator = Iterator;

	IndexRange(size_t begin, size_t end) :
		begin_(begin),
		end_(end)
	{
	}

    Iterator begin() const {
		return Iterator(begin_);
	}

	Iterator end() const {
		return Iterator(end_);
	}

	ReverseIterator rbegin() const {
		return ReverseIterator(Iterator(end_));
	}

	ReverseIterator rend() const {
		return ReverseIterator(Iterator(begin_));
	}

private:

	size_t begin_;

	size_t end_;

};

} // namespace utils

using utils::IndexRange;

} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_INDEXRANGE_HPP_ */
