#include "looseOnString.h"

template<typename CharT>
bool BasicLooseOnString<CharT>::attach(BasicComment<CharT> & comment,
		 const_iter search_begin) const
{
	/* declarations of all the range iterators */

	/* where I'm looking */
	IterT in_begin(search_begin, Parent::on_str->end(), lowest, highest);
			// search untill end of commented on string
	IterT in_end(Parent::on_str->end(), Parent::on_str->end(), 
			lowest, highest);

	/* what I'm searching for */
	IterT for_begin(comment.on.begin(),comment.on.end(),
			lowest, highest);
	IterT for_end(comment.on.end(), comment.on.end(),
			lowest, highest);

	IterT begin = std::search(in_begin, in_end, for_begin, for_end);

	// on failure, std::search returns where searched untill
	if(begin != Parent::on_str->end()) {
		comment.begin = begin;
		
		// can't just add length of comment.on 
		// b/c find may be smaller as skip chars

		/*****************************************************
		 *Notice that I specifically call find_end with begin*
		 *not with comment.begin. This is because I want to  *
		 ***************use the rangeIterator*****************
		 *****************************************************/
		comment.end = std::find_end(begin, in_end, for_begin, for_end);

		Parent::last_search_begin = search_begin;
		Parent::last_find_end = comment.end;

		return 1;
	} else {
		return 0;
	}
}

#include <iostream>

template<typename CharT>
bool BasicLooseOnString<CharT>::attach(BasicComment<CharT> & comment, 
	typename BasicOnString<CharT>::AttachMode mode) const
{
	switch(mode)
	{
		case Parent::begin:
			return attach(comment,Parent::on_str->begin());
		case Parent::stay:	
			return attach(comment,Parent::last_search_begin);
		case Parent::proceed:
			return attach(comment,Parent::last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}
