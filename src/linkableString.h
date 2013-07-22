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
public:
	bool addLink(const Link & a_link);
	void next();
	bool hasLink() {
		return (link_queue.empty())? 0: 
			link_queue.back().range == range;
	}
	Link & link() { return link_queue.back(); }
	String string() { 
		return m_string.substr(range.start, range.rangeSize());
	}
	bool finished() { return range.finish == m_string.length(); }

};

typedef BasicLinkableString<char> LinkableString;
typedef BasicLinkableString<wchar_t> LinkableWString;

#endif
