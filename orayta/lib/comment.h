#ifndef COMMENT_H
#define COMMENT_H

#include <string>

template<typename CharT>
struct BasicComment
{
	typedef std::basic_string<CharT> String;
	String on;	// what is being commented on
			// not neccisarily the whole e.g. story
	String comment;

	/* begin and end of what commented on in source string */
	typename String::const_iterator begin;
	typename String::const_iterator end;

	BasicComment() {}
	BasicComment(String a_on = String(), String a_comment = String()) { 
		on = a_on, comment = a_comment;
	}

	static const String kludge;
	bool linked() { 
		return begin != kludge.end();
	}
};

typedef BasicComment<char> Comment;
typedef BasicComment<wchar_t> WComment;

#endif
