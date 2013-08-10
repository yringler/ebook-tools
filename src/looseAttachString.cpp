#include "looseAttachString.h"

template<typename CharT>
bool BasicLooseAttachString<CharT>::attach(BasicLink<CharT> & link, 
		const_iter search_begin) const
{
	/* declarations of all the range iterators */

	/* where I'm looking */
	IterT in_begin(search_begin, lowest, highest);
	IterT in_end(Parent::to_str->end, lowest, highest);

	/* what I'm searching for */
	IterT for_begin(link.link.begin(), lowest, highest);
	IterT for_end(link.link.end(), lowest, highest);

	const_iter begin = std::search(in_begin, in_end, for_begin, for_end);

	if(begin != Parent::to_str->end()) {
		link.begin = begin;
		link.end = begin + link.link.length();

		Parent::last_search_begin = search_begin;
		Parent::last_find_end = link.end;

		return 1;
	} else {
		return 0;
	}
}
template<typename CharT>
bool BasicLooseAttachString<CharT>::attach(BasicLink<CharT> & link, 
	typename BasicAttachString<CharT>::AttachMode mode) const
{
	switch(mode)
	{
		case Parent::begin:
			return attach(link,Parent::to_str->begin());
		case Parent::stay:	
			return attach(link,Parent::last_search_begin);
		case Parent::proceed:
			return attach(link,Parent::last_find_end);
		default:
			std::cerr << "attach:error:bad mode\n";
			throw;
	}
}
