#ifndef BOOK_H
#define BOOK_H

#include<deque>
#include<string>
#include "division.h"
#include "location.h"

template<typename ContentT, typename CharT>
class Book : public std::deque<Division<ContentT, CharT> > {
private:
	typedef std::deque<Division<ContentT, CharT> deque;

	std::basic_string<CharT> m_title;
	std::basic_string<CharT> & title() { return m_title; }
	typedef std::iterator <
	      typename std::forward_iterator_tag,
	      typename std::iterator_traits<deque::iterator>::value_type,
	      typename std::iterator_traits<deque::iterator>::difference_type,
	      typename std::iterator_traits<deque::iterator>::pointer,
	      typename std::iterator_traits<deque::iterator>::reference>
			 > ForwardIterator;

public:
	void title(const std::basic_string<CharT> & at) { m_title = at; }


	// most divisions don't point to content. This iterator only lands on
	// those
	// The inherited iterator is good for output, the skip is good for 
	// in program processing, eg{ie?} linking
	class content_iterator : ForwardIterator
	{
	private:
		ForwardIterator m_base;
		Location<ContentT, CharT> m_location;
	public:
		content_iterator(ForwardIterator ai) : m_base(ai) { m_location.add(*m_base); }

		ValueT & operator*() const { return *m_base; }
		operator++() {
			// entry check is a no no, because its almost always
			// going to be called from a division which has content
			do {
				++m_base;
				m_location.add(*m_base);
			} while(not operator*().has_content());
		}
		operator++(int) {
			operator++();
		}
		
		// to fullfill the requirements of a forward_iterator
		// I want to be this, because skipping with addition is hard
		bool operator==(const RangeIterator & iter) const
			{ return m_base == iter.m_base; }
		bool operator!=(const RangeIterator & iter) const
			{ return m_base != iter.m_base; }


	};

	content_iterator content_iterator_begin() { return content_iterator(begin()); }
	content_iterator content_iterator_end() { return content_iterator(end()); }
};

#endif
