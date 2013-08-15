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
	// convenionce function: returns a copy, but diffrent this->current
	RangeIterator & diffLocCopy(RangeIterator iter) {
		return RangeIterator(iter,end,lowest,highest);
	}
public:
	// args: the initial place to point to, the past-the-end iterator,
	// and acceptable range of the values
	RangeIterator(Iterator  a_current, Iterator  a_end,
			ValueT a_lowest, ValueT a_highest) {
		current = a_current;
		end = a_end;
		lowest = a_lowest;
		highest = a_highest;
	}
	RangeIterator() {} 
	Iterator base() const { return current; }
	ValueT operator*() const { return *current; }
	RangeIterator & operator++() {
		// while out of range
		while(*current < lowest && *current > highest 
				&& current != end) {
			current++;
		}
		return *this;
	}
	Iterator & operator++(int) { return operator++(); }
	bool operator==(RangeIterator iter) { return current == iter.current; }
	bool operator!=(RangeIterator iter) { return current != iter.current; }
	bool operator<=(RangeIterator iter) { return current <= iter.current; }
	bool operator>=(RangeIterator iter) { return current >= iter.current; }
	typename std::iterator_traits<Iterator>::difference_type
		operator-(RangeIterator iter) {
			return current - iter.current;
		}
	RangeIterator operator-(int i) { return diffLocCopy(current - i); }
	RangeIterator operator+(int i) { return diffLocCopy(current + i); }
	ValueT & operator[](int i) { return current[i]; }
};

#endif
