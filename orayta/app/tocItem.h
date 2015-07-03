#ifndef TOC_ITEM_H
#define TOC_ITEM_H

#include <deque>
#include <string>
#include <cassert>
#include "../src/sharedAutoPtr.h"

/*
 * Bear in mind: each TocItem refrences one "smallest text division"
 * You're going to be useing a lot of TocItems
 *
 * This is a *WTA* and a *deque* smooshed together
 * WTA: Way To Access. Access the smallest division of (I guess) EXTERNALY
 * stored text.
 * eg an array of strings for the entire book, each element a paragraph -
 * WTA is to the strings
 *
 * Deque: contains all *descriptions* of the refrenced text
 * Description: MUST contain the *depth*. Should contain the *number* and a 
 * *lable*, but only needs one.
 * 	Depth: an int represents the depth. A lower number is *shallow*. A
 * 	  higher number is *deeper*.
 * 	  Shallow: =general. A chapter might be the shallowest book division
 * 	  Deep: =particular. A paragraph might be the deepest book division
 *   	  (All chapters {in all TocItems} will have the same depth, maybe 0,
 *   	  depending on the book structure.)
 * 	Number: eg 1 for chapter 1, etc
 *	Lable: eg "In which an ox falls into a pit" for chapter 1
 *      (Generally, there should be only one 1 for a given depth, but a lable
 *      could show up twice {at the same depth of diffrent TocItems} I suppose)
 * 	
 * Very important method:
 * 	diff(otherTocItem) - compares the two description queues of the TocIems,
 * 	returns the first depth that has a different description, terminate if
 * 	there isn't one. Thats harsh, but I don't think that should ever happen
 * 	If it does I'll reconsider
 */

// T=type pointing to, CharT is for title
template<typename T, typename CharT>
class BasicTocItem {
private:
	typedef std::basic_string<CharT> String;
		/* eg name of book and chapter and... */
	struct Description { SharedAutoPtr<String> name; int num; };
	std::deque<Description> desc;
	/* 
	 * the eg chapter. This should provide access to 
	 * the whole eg chapter, not just the first eg paragraph
	 */
	T * place;
public:
	//BasicTocItem(BasicTocItem & base) : desc(base.names()) {}
		/* depth starts from 0 size from 1 */
	int depth() { return desc.size() - 1; }
	void add(const String & str, int a_depth, int a_num=0) {
			/* depth + 1 to allow adding */
		assert((a_depth >= 0) && (a_depth <= (depth() + 1)));
		desc.resize(a_depth + 1);	// I hate all this +/-1 stuff
		desc.back().name = new String(str);
		desc.back().num = a_num;
	}
	
	void set(T & t) { place = &t; }	
	T & get() { return *place; }
};

#endif
