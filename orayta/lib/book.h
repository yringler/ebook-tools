#ifndef BOOK_H
#define BOOK_H

#include<deque>
#include<string>

template<typename ContentT, typename CharT>
struct Book : public std::deque<ContentT> {
	std::basic_string<CharT> title;
};

#endif
