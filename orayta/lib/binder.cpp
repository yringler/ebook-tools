#include <algorithm>
#include <iostream>
#include "binder.h"

template<typename CharT>
bool BasicBinder<CharT>::attach(BasicComment<CharT> & link,
		 const_iter search_begin) const
{
	typename String::const_iterator begin;
	begin = std::search(search_begin, to_end,
			link.on.begin(), link.on.end());

	if(begin != to_end) {
		link.begin = begin;
		link.end = begin + link.on.length();

		last_search_begin = search_begin;
		last_find_end = link.end;

		return 1;
	} else {
		return 0;
	}
}

#include <iostream>

template<typename CharT>
bool BasicBinder<CharT>::attach(BasicComment<CharT> & link, 
		AttachMode mode) const
{
	switch(mode)
	{
		case first:	return attach(link,to_begin);
		case same:	return attach(link,last_search_begin);
		case next:	return attach(link,last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}
