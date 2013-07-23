#ifndef LINKABLE_STRING_CPP
#define LINKABLE_STRING_CPP

#include "linkableString.h"
#include <iostream>

template<typename CharT>
bool BasicLinkableString<CharT>::addLink(Link & a_link) 
{ 
	int search_start = (link_queue.empty())? 0: 
		link_queue.front().range.finish + 1;
	int link_start = String::find(a_link.link, search_start);

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
void BasicLinkableString<CharT>::start()
{
	if(link_queue.empty()) {
		range.start = 0;
		range.finish = String::length();
	} else if(link_queue.back().range.start == 0) {
		range = link_queue.back().range;
	} else {
		range.start = 0;
		range.finish = link_queue.back().range.start - 1;
	}
}
#include <iostream>
template<typename CharT>
void BasicLinkableString<CharT>::next()
{
	if(finished()) {
		return;
	} else if(hasLink()){
		link_queue.pop_back();
	}

	if(link_queue.empty() && not finished()) {
		// if I am on the last link
		range.start = range.finish + 1;
		range.finish = String::length();
	} else if(link_queue.back().range.start > range.finish + 1) {
		// if theres stuff before the next linked to text
		range.start = range.finish + 1;
		range.finish = link_queue.back().range.start - 1;
	} else if(link_queue.back().range.start == range.finish + 1){	
		range = link_queue.back().range;
	} else {
		std::cerr << "linkableString:next():error\n";
		throw;
	}
}

#endif
