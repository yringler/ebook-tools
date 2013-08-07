#ifndef LINK_H
#define LINK_H

#include <string>

template<typename CharT>
struct BasicLink
{
	typedef std::basic_string<CharT> String;
	String link;
	String text;

	/* begin and end in source string */
	typename String::const_iterator begin;
	typename String::const_iterator end;

	BasicLink(String a_link = String(), String a_text = String()) { 
		link = a_link, text = a_text;
	}
};

typedef BasicLink<char> Link;
typedef BasicLink<wchar_t> WLink;

#endif
