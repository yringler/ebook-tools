#include "linkableString.h"

template<typename CharT>
bool BasicLinkableString<CharT>::addLink(const Link & a_link) 
{ 
	int search_start = (link_queue.empty())? 0: 
		link_queue.front().finish + 1;
	int link_start = m_string.find(a_link.link, search_start);

	if(link_start == String::npos) {
		return 0;
	} else {
		a_link.range.start = link_start;
	// subtract 1 because first char counted in length is link_start
		a_link.range.finish = link_start + a_link.link.length() - 1;
		link_queue.push_front(a_link);
		return 1;

	}
}
template<typename CharT>
void BasicLinkableString<CharT>::next()
{
	if(hasLink()) link_queue.pop_back();
	Range *link_range = (link_queue.empty())? 0: &link_queue.back().range;

	if(link_queue().empty()) {
		if(not finished()) {	// if I didn't do this already
			range.start = range.finish + 1;
			range.finish = m_string.length();
		}
	} else if(link_queue.back().start > range.finish + 1) {
		// if theres stuff before the next linked to text
		range.start = range.finish + 1;
		range.finish = link_range->start - 1;
	} else {	// assumed equal to
		range = *link_range;
	}
}
