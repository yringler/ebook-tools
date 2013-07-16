#include "linkableString.h"

template<typename CharT>
bool BasicLinkableString<CharT>::addLink(const Link & a_link) 
{ 
	int link_start = m_string.find(a_link.link(), link_search_start);
	if(link_start == String::npos) {
		return 0;
	} else {
		a_link.range().start(link_start);
	// subtract 1 because first char counted in length is link_start
		a_link.range.finish(link_start + m_string.length() - 1);
		int size_not_linked = link_start - link_search_start;

		link_search_start += size_not_linked + a_link.link().size();
		link_queue.push_front(a_link);
	}
}
template<typename CharT>
void BasicLinkableString<CharT>::next()
{
	if(hasLink()) link_queue.pop_back();
	Range *link_range = (link_queue.empty())? 0: &link_queue.back().range();

	if(link_queue().empty()) {
		range.start(range.finish() + 1);
		range.finish(m_string.length());
	} else if(link_queue->start() > range.finish() + 1) {
		range.start(range.finish() + 1);
		range.finish(link_range->start() - 1);
	} else {	// assumed equal to
		range = *link_range;
	}
}
