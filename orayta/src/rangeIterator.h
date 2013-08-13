#ifndef RANGE_ITERATOR_H
#define RANGE_ITERATOR_H

/* A wrapper around an iterator. operator++ skips over values within range */
/* the beggining and end of range are acceptable values */
template <typename ValueT, class IterT>	// type of the iterator and *iterator
class RangeIterator : public IterT
{
private:
	IterT end;	// so doesn't skip past the end

	ValueT lowest;
	ValueT highest;
public:
	// the initial place to point to, the past-the-end iterator,
	// and acceptable range of the values
	RangeIterator(IterT & start, IterT & a_end, ValueT a, ValueT b)
		: IterT(start)
	{
		end = a_end;
		lowest = a, end = b;
	}
	RangeIterator() {}

	void set(IterT start, IterT a_end) { operator=(start), end = a_end; }
	virtual ValueT operator*() const { return IterT::operator*(); }
	virtual void operator++() {
		while(*this <= lowest && *this >= highest &&  this != end) {
			IterT::operator++();
		}
	}
	virtual void operator++(int) { operator++(); }
};

#endif
