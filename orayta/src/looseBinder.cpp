#ifndef LOOSE_BINDER_CPP
#define LOOSE_BINDER_CPP

#include "looseBinder.h"
#include <iostream>
#include <utility>

template<typename CharT>
bool BasicLooseBinder<CharT>::attach(BasicComment<CharT> & comment,
		 const_iterator search_begin) const
{
	typedef RangeIterator<const_iterator> IterT;

		/* declarations of all the range iterators */

	/* where I'm looking ; ie I'm looking *in* this substring */
	IterT in_begin(search_begin, Parent::to_end, lowest, highest);
			// search untill end of commented on string
	IterT in_end(Parent::to_end, Parent::to_end, lowest, highest);

	/* what I'm searching for */
	IterT for_begin(comment.on.begin(),comment.on.end(), lowest, highest);
	IterT for_end(comment.on.end(), comment.on.end(), lowest, highest);

	// begining of where comment is on
	IterT find_begin = std::search(in_begin, in_end, for_begin, for_end);

	// on failure, std::search returns where searched untill ; ie end()
	if(find_begin != in_end) {
		
		/*
		 * We'll just increment these both, one at a time, untill we've
		 * hit for_end, the end of comment.on
		 * this incrementation only goes through chars in range.
		 */
			// points to char in source string
		IterT in_cmp = in_begin; 
			// points to char in comment.on string
		IterT for_cmp = for_begin;
		
		while(for_cmp != for_end)
			for_cmp++, in_cmp++;
		in_cmp++;

		comment.begin = find_begin.base();
		comment.end = in_cmp.base();

		Parent::last_search_begin = search_begin;
		Parent::last_find_end = comment.end;

		return 1;
	} else {
		return 0;
	}
}

#include <iostream>

template<typename CharT>
bool BasicLooseBinder<CharT>::attach(BasicComment<CharT> & comment, 
	typename Parent::AttachMode mode) const
{
	switch(mode)
	{
		case Parent::first:
			return attach(comment,Parent::to_begin);
		case Parent::same:	
			return attach(comment,Parent::last_search_begin);
		case Parent::next:
			return attach(comment,Parent::last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}

#endif
