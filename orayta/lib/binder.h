#ifndef BINDER_H
#define BINDER_H

#include <string>
#include <cassert>
#include "comment.h"

/*
 * Binds a comment to source string.
 * Source string stored in begin and end const iterators
 * 	refrencable by public methods to prevent type mismatch
 * 	when a non-const source is used with a const comment iterator
 */
template<typename CharT>
class BasicBinder
{
private:
	typedef std::basic_string<CharT> String;
	typedef typename String::iterator IterT;

protected:
	// iterators to commented-on string
	IterT to_begin;
	IterT to_end;	// must{?} be past the end for stl compatibility

	mutable IterT last_search_begin;	
	mutable IterT last_find_end;
	virtual bool attach(BasicComment<CharT> & comment,
			IterT search_begin) const;
public:
	enum AttachMode { first, same, next };
public:
	BasicBinder(String & str) { to(str); }
	BasicBinder() {}

	void restart() { last_search_begin = last_find_end = to_begin; }
	virtual void to(IterT a, IterT b) { 
		// no empty strings, please
		assert(a != b);

		to_begin = a;
		to_end = b;

		restart();
	}
	virtual void to(const String & str) { to(str.begin(), str.end() ); }

	virtual bool attach(BasicComment<CharT> & comment,
			AttachMode mode=next);

	IterT & begin() { return to_begin; }
	IterT & end() { return to_end; }
};

#include "binder.cpp"

typedef BasicBinder<char> Binder;
typedef BasicBinder<wchar_t> WBinder;

#endif
