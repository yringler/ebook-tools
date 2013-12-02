#ifndef TOC_ITEM_H
#define TOC_ITEM_H

#include <deque>
#include <string>
#include <cassert>
#include "../src/sharedAutoPtr.h"

/*
 * This is basically a deque and a refrence smooshed together
 * Purpose: n-deep subsection lables, access to start of subsection
 * 	depth is counted from 0, which is probably the whole book
 * Contains: a pointer to the start of section
 *	deque of unique_ptrs to string
 * Semi-Random Method That I Chucked In Because Its Conveniant:
 * 	diff(other) - returns the lowest diffrent index
 * 		terminate if there isn't one
 * 		thats harsh, but I don't think that should ever happen
 * 		if it does I'll reconsider
 * Example: a toc item representing third paragraph of chapter seven:
 * 	depth 0 = pointer to pre-existing book title
 * 	1 to pre-existing chapter, and 2 to the paragraph title
 */

// T=type pointing to, CharT is for title
template<typename T, typename CharT>
class BasicTocItem {
private:
	typedef std::basic_string<CharT> String;
		/* eg name of book and chapter and... */
	std::deque<sharedAutoPtr<String> names;
	/* 
	 * the eg chapter. This should provide access to 
	 * the whole eg chapter, not just the first eg paragraph
	 */
	T * place;
public:
	BasicTocItem(BasicTocItem & base) : names(base.names()) {}
		/* depth starts from 0 size from 1 */
	int depth() { return names.size() - 1; }
	void add(const String & str, int a_depth) {
			/* depth + 1 to allow adding */
		assert((a_depth >= 0) && (a_depth <= (depth() + 1)));
		names.resize(a_depth + 1);	// I hate all this +/-1 stuff
		names.back() = new String(str);
	}
	
	void set(T & t) { place = t; }	
	T & get() { return *place; }
};

#endif
