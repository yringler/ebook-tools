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
	// the string which is being commented on
	// enables simple insertion of comment into source text
	// not graceful. idea?
	String *commented;

	/* begin and end of what commented on in source string */
	typename String::iterator begin;
	typename String::iterator end;

	BasicComment() { commented = 0; }
	BasicComment(String a_on = String(), String a_comment = String()) { 
		commented = 0;
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
