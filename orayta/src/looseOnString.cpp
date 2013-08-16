#include "looseOnString.h"
#include <iostream>

template<typename CharT>
bool BasicLooseOnString<CharT>::attach(BasicComment<CharT> & comment,
		 const_iterator search_begin) const
{
	typedef RangeIterator<const_iterator> IterT;

		/* declarations of all the range iterators */

	/* where I'm looking */
	IterT in_begin(search_begin, Parent::on_str->end(), lowest, highest);
			// search untill end of commented on string
	IterT in_end(Parent::on_str->end(), Parent::on_str->end(), 
			lowest, highest);

	/* what I'm searching for */
	IterT for_begin(comment.on.begin(),comment.on.end(), lowest, highest);
	IterT for_end(comment.on.end(), comment.on.end(), lowest, highest);

	// begining of where comment is on
	IterT tmp = std::search(in_begin, in_end, for_begin, for_end);

	// on failure, std::search returns where searched untill ie end()
	if(tmp != in_end) {
		comment.begin = tmp.base();
		
		// can't just add length of comment.on 
		// b/c find may be smaller as skip chars

		// use tmp, not comment.begin, because want RangeIterator
		//tmp = std::find_end(in_begin, in_end, for_begin, for_end);
		//comment.end = tmp.base();
		comment.end = tmp.base() + comment.on.length();

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
