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
		comment.begin = find_begin.base();
		
		// can't just add length of comment.on 
		// b/c find may be smaller as skip chars

		std::pair<IterT,IterT> mismatch;
		mismatch = std::mismatch(find_begin,in_end, for_begin);
		comment.end = mismatch.first.base();
		//comment.end = find_begin.base() + comment.on.length();

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
