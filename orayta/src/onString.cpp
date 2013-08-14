#include <algorithm>
#include <iostream>
#include "onString.h"

template<typename CharT>
bool BasicOnString<CharT>::attach(BasicComment<CharT> & link,
		 const_iter search_start) const
{
	typename String::const_iterator begin;
	begin = std::search(search_start, on_str->end(),
			link.on.begin(), link.on.end());

	if(begin != on_str->end()) {
		link.begin = begin;
		link.end = begin + link.on.length();

		last_search_start = search_start;
		last_find_end = link.end;

		return 1;
	} else {
		return 0;
	}
}

#include <iostream>

template<typename CharT>
bool BasicOnString<CharT>::attach(BasicComment<CharT> & link, 
		AttachMode mode) const
{
	switch(mode)
	{
		case begin:	return attach(link,on_str->begin());
		case stay:	return attach(link,last_search_start);
		case proceed:	return attach(link,last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}
