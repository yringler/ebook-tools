#ifndef LINK_H
#define LINK_H

#include <string>
#include "range.h"

template<typename CharT>
struct BasicLink
{
	typedef std::basic_string<CharT> String;
	String link;
	String text;
	Range range;

	BasicLink(String a_link, String a_text) { 
		link(a_link, a_text);
	}
	BasicLink() {}
};
typedef BasicLink<char> Link;
typedef BasicLink<wchar_t> WLink;
#endif
