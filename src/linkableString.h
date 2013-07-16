#ifndef LINKABLE_STRING_H
#define LINKABLE_STRING_H

#include <deque>
#include "range.h"
#include "link.h"

template<typename CharT>
class BasicLinkableString
{
private:
	typedef std::basic_string<CharT> String;
	typedef BasicLink<CharT> Link;
	String m_string;
	std::deque<Link> link_queue;
	Range range;
	int link_search_start;	// where the next search for a link should start
public:
	BasicLinkableString() : link_search_start(0) {}
	bool addLink(const Link & a_link);
	void next();
	bool hasLink() {
		return (link_queue.empty())? 0: 
			link_queue.back().range() == range;
	}
	Link & link() { if(hasLink()) return link_queue.back(); else throw; }
	String string() { 
		return m_string.substr(range.start(), range.rangeSize());
	}
	bool finished() { return range.finish() == m_string.length(); }

};

typedef BasicLinkableString<char> LinkableString;
typedef BasicLinkableString<wchar_t> LinkableWString;

#endif
