#ifndef LOCATION_H
#define LOCATION_H

#include <deque>
#include <string>
#include <cassert>

#include "division.h"

/* 
 * 	The theory is that location implies the exact location of a given piece
 * 	of text, and that a location is comprised of the full list of all the
 * 	divisions that said text is located at. I think its clever and
 * 	graceful.
 *
 *	********
 *	* NOTE *
 *	********
 * 	If you add a division of lesser depth than
 * 	the current final depth than all greater depths are deleted and that
 * 	depth is replaced.
 *
 * 	Important method:
 * 	bool diff(otherLocation) - compares the two description queues of the
 * 	TocIems, returns the first depth that has a different description,
 * 	terminate if there isn't one. Thats harsh, but I don't think that
 * 	should ever happen If it does I'll reconsider
 */

template<typename CharT>
class BasicLocation {
private:
	typedef std::basic_string<CharT> String;
		/* eg name of book and chapter and... */
	typedef BasicDivision<CharT> Division;

	std::deque<Division> divs;
public:
	std::deque<Division>::iterator begin() { return divs.begin(); }
	std::deque<Division>::iterator end() { return divs.end(); }

	int depth() { return divs.back().depth; }
	// add another divion that text belongs to
	void add(const Division & div) {
		// depth + 1 to allow adding
		assert((div.depth >= 0) && (div.depth <= depth()+1));

		if(divs.empty())
			assert(divs.depth == 0);
		else if(div.depth < divs.back().depth)
	       /* 
		* depth starts at zero, size from one.
		* resizing to div.depth means that from the current div of that
		* depth and on are deleted, allowing push_back to work
		* properly.  This is a clever, ergo dangerous, way of saving an
		* asignment, but too clean to pass up
		*/
			divs.resize(div.depth);
		
		divs.push_back(div);
	}
	void add(int a_depth, const String & name, int a_num=0) {
		Division desc;
		desc.name = name;
		desc.depth = a_depth;
		desc.num = a_num;

		add(desc);
	}
	
	int diff(const BasicLocation<T, CharT> & t) {
		if (depth() != t.depth()) throw "location:diff:same depth";

		// if the data exists as seperate entities, there should be a
		// division to represent that. If there isn't, you'll just have
		// to put up with the terminations.
		if (operator==(t)) throw "location:diff:=";
		else return pair.first->depth;
	}

	bool operator==(BasicLocation & t) {
		typedef typename std::deque<Division>::const_iterator iter;
		std::pair<iter, iter> pair;

		pair = std::mismatch(divs.begin(),divs.end(), t.divs.begin());
		/*
		 * All ye who enter here, despair of comprehension
		 *
		 * true if all values compared matched
		 * THIS IS ALSO TRUE IF ONE QUEUE IS SMALLER
		 * more general matches *all* more particular locations
		 */
		return *pair.first == divs.end() && *pair.second == t.end();
	}
};

typedef BasicLocation<char> Location;
typedef BasicLocation<wchar_t> WLocation;

#endif
