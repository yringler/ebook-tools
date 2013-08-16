#ifndef ON_STRING_H
#define ON_STRING_H

#include <string>
#include <memory>
#include "comment.h"

// a string which is commented on
// main feature is connecting comments to itself
template<typename CharT>
class BasicOnString
{
private:
	typedef std::basic_string<CharT> String;
	typedef typename String::const_iterator const_iter;

protected:
	// the string that is being commented on
	std::auto_ptr<const String> on_str;

	mutable const_iter last_search_begin;	
	mutable const_iter last_find_end;
	virtual bool attach(BasicComment<CharT> & comment,
			const_iter search_begin) const;
public:
	enum AttachMode { begin, stay, proceed };
public:
	BasicOnString(String & str) { to(str); }
	BasicOnString() {}
	const String & get() { return *on_str; }
	virtual void set(const String & str) { 
		on_str.reset(new const String(str));

		last_search_begin = on_str->begin();
		last_find_end = on_str->begin();
	}
	void operator=(const String & str) { set(str); }
	virtual bool attach(BasicComment<CharT> & comment,
			AttachMode mode=proceed) const;
};

#include "onString.cpp"

typedef BasicOnString<char> OnString;
typedef BasicOnString<wchar_t> WOnString;

#endif
