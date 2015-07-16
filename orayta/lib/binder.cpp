#include <algorithm>
#include <iostream>
#include "binder.h"

template<typename CharT>
bool BasicBinder<CharT>::attach(BasicComment<CharT> & comment,
		 const_iter search_begin) const
{
	typename String::const_iterator begin;
	begin = std::search(search_begin, to_end,
			comment.on.begin(), comment.on.end());

	if(begin != to_end) {
		comment.begin = begin;
		/* 
		 * end is past the end
		 * eg |start|end|past|
		 * length == 2
		 * start + 2 = past
		 */
		comment.end = begin + comment.on.length();

		last_search_begin = search_begin;
		last_find_end = comment.end;

		return 1;
	} else {
		return 0;
	}
}

#include <iostream>

template<typename CharT>
bool BasicBinder<CharT>::attach(BasicComment<CharT> & comment, 
		AttachMode mode) const
{
	switch(mode)
	{
		case first:	return attach(comment,to_begin);
		case same:	return attach(comment,last_search_begin);
		case next:	return attach(comment,last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}
