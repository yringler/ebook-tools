#ifndef RANGE_ITERATOR_H
#define RANGE_ITERATOR_H

#include <iterator>
#include <iostream>

/* A wrapper around an iterator. operator++ skips over values outside range */
/* the beggining and end of range are acceptable values */
// ( design from std::reverse_iterator, as written in c++ in a nutshell )
template <class Iterator>
class RangeIterator : public std::iterator<
	      typename std::forward_iterator_tag,
	      typename std::iterator_traits<Iterator>::value_type,
	      typename std::iterator_traits<Iterator>::difference_type,
	      typename std::iterator_traits<Iterator>::pointer,
	      typename std::iterator_traits<Iterator>::reference>
{
private:
	typedef typename std::iterator_traits<Iterator>::value_type ValueT;

	Iterator current;	// current location
	Iterator end;	// so doesn't skip past the end

	// range of values not to skip
	ValueT lowest;
	ValueT highest;
protected:
	// warning: this is a finicky function. its given me a lot of trouble
	bool should_increment() { return ( current != end &&
			(*current < lowest || *current > highest) ); }
public:
	// args: the initial place to point to, the past-the-end iterator,
	// and acceptable range of the values
	RangeIterator(Iterator  a_current, Iterator  a_end,
			ValueT a_lowest, ValueT a_highest) {
		current = a_current;
		end = a_end;
		lowest = a_lowest;
		highest = a_highest;
		
		if(should_increment()) operator++();
	}
	RangeIterator(const RangeIterator & iter) { *this = iter; }
	RangeIterator() {} 
	Iterator base() const { return current; }

	// const ValueT operator*() const { return *current; }
	ValueT operator*() const { return *current; }
	// I think that'll work...
	// const ValueT operator->() const { return *current; }
	//ValueT & operator->() { return *current; }


	RangeIterator & operator++() {
		do {
			current++;
		} while(should_increment());

		return *this;
	}
	RangeIterator & operator++(int) { return operator++(); }

	bool operator==(const RangeIterator & iter) const
		{ return current == iter.current; }
	bool operator!=(const RangeIterator & iter) const
		{ return current != iter.current; }
};

#endif
