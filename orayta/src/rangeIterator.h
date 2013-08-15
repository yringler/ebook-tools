#ifndef RANGE_ITERATOR_H
#define RANGE_ITERATOR_H

#include <iterator>

/* A wrapper around an iterator. operator++ skips over values within range */
/* the beggining and end of range are acceptable values */
// ( design from std::reverse_iterator, as written in c++ in a nutshell )
template <class Iterator>
class RangeIterator : public std::iterator<
	      typename std::iterator_traits<Iterator>::iterator_category,
	      typename std::iterator_traits<Iterator>::value_type,
	      typename std::iterator_traits<Iterator>::diffrence_type,
	      typename std::iterator_traits<Iterator>::pointer,
	      typename std::iterator_traits<Iterator>::refrence>
{
private:
	typedef typename std::iterator_traits<Iterator>::value_type ValueT;

	Iterator current;	// current location
	Iterator end;	// so doesn't skip past the end

	// range of values not to skip
	ValueT lowest;
	ValueT highest;
public:
	// the initial place to point to, the past-the-end iterator,
	// and acceptable range of the values
	RangeIterator(Iterator & a_current, Iterator & a_end,
			ValueT a_lowest, ValueT a_highest) {
		current = a_current;
		end = a_end;
		lowest = a_lowest;
		highest = a_highest;
	}

	ValueT operator*() const { return *current; }
	void operator++() {
		while(*this <= lowest && *this >= highest &&  this != end) {
			current++;
		}
	}
	void operator++(int) { operator++(); }
};

#endif
