#ifndef ATTACH_LINK_H
#define ATTACH_LINK_H

#include <string>
#include "link.h"

// where to search for link

template<typename CharT>
class BasicAttachLink
{
private:
	typedef std::basic_string<CharT> String;
	typedef typename String::const_iterator const_iter;

// the string that will link to public:
	const String *to_str;	
protected:
	const_iter last_search_start;	
	const_iter last_find_end;
	bool attach(BasicLink<CharT> & link,
		 const_iter search_start);
public:
	enum AttachMode { begin, stay, proceed };
public:
	BasicAttachLink(String & str) { to(str); }
	BasicAttachLink(String * str) { to(str); }
	void to(const String * str) { 
		to_str = str;
		last_search_start = to_str->begin();
		last_find_end = to_str->begin();
	}
	void to(const String & str) { to(&str); }
	bool attach(BasicLink<CharT> & link, AttachMode mode=proceed);

};

#include "attachLink.cpp"

typedef BasicAttachLink<char> AttachLink;
typedef BasicAttachLink<wchar_t> WAttachLink;

#endif
