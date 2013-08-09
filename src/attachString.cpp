#include <algorithm>
#include <iostream>
#include "attachString.h"

template<typename CharT>
bool BasicAttachString<CharT>::attach(BasicLink<CharT> & link,
		 const_iter search_start) const
{
	typename String::const_iterator begin;
	begin = std::search(search_start, to_str->end(),
			link.link.begin(), link.link.end());

	if(begin != to_str->end()) {
		link.begin = begin;
		link.end = begin + link.link.length();

		last_search_start = search_start;
		last_find_end = link.end;

		return 1;
	} else {
		return 0;
	}
}

#include <iostream>

template<typename CharT>
bool BasicAttachString<CharT>::attach(BasicLink<CharT> & link, 
		AttachMode mode) const
{
	switch(mode)
	{
		case begin:	return attach(link,to_str->begin());
		case stay:	return attach(link,last_search_start);
		case proceed:	return attach(link,last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}
