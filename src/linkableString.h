#ifndef LINKABLE_STRING_H
#define LINKABLE_STRING_H

#include <deque>
#include <string>
#include "range.h"
#include "link.h"

template<typename CharT>
class BasicLinkableString : std::basic_string<CharT>
{
private:
	typedef std::basic_string<CharT> String;
	typedef BasicLink<CharT> Link;
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
	std::basic_string<CharT> curStr() { 
		return String::substr(range.start, 
				range.rangeSize());
	}
	bool finished() { return range.finish == 
		String::length();
	}

};

typedef BasicLinkableString<char> LinkableString;
typedef BasicLinkableString<wchar_t> LinkableWString;

#endif
