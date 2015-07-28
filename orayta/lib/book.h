#ifndef BOOK_H
#define BOOK_H

#include<deque>
#include<string>
#include "division.h"
#include "location.h"

template<typename ContentT, typename CharT>
class Book : public std::deque<Division<ContentT, CharT> > {
private:
	std::basic_string<CharT> m_title;
	std::basic_string<CharT> & title() { return m_title; }
public:
	void title(const std::basic_string<CharT> & at) { m_title = at; }
};

#endif
