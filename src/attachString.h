#ifndef ATTACH_LINK_H
#define ATTACH_LINK_H

#include <string>
#include <memory>
#include "link.h"

// where to search for link

template<typename CharT>
class BasicAttachString
{
private:
	typedef std::basic_string<CharT> String;

	// the string that will link to
	std::auto_ptr<const String> to_str;
protected:
	typedef typename String::const_iterator const_iter;
	mutable const_iter last_search_start;	
	mutable const_iter last_find_end;
	virtual bool attach(BasicLink<CharT> & link, const_iter search_start)
		const;
public:
	enum AttachMode { begin, stay, proceed };
public:
	BasicAttachString(String & str) { to(str); }
	BasicAttachString() {}
	const String & get() { return *to_str; }
	virtual void set(const String & str) { 
		to_str.reset(new const String(str));

		last_search_start = to_str->begin();
		last_find_end = to_str->begin();
	}
	void operator=(const String & str) { set(str); }
	virtual bool attach(BasicLink<CharT> & link, AttachMode mode=proceed) 
		const;

};

#include "attachString.cpp"

typedef BasicAttachString<char> AttachString;
typedef BasicAttachString<wchar_t> WAttachString;

#endif
