#ifndef LOCATION_H
#define LOCATION_H

#include <deque>
#include <string>
#include <cassert>
#include <mismatch header>

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

template<typename DataT, typename CharT>
class Location {
private:
	typedef std::basic_string<CharT> String;
		/* eg name of book and chapter and... */
	typedef Division<DataT, CharT> Division;

	std::deque<Division> divs;
public:
	void add(const Division & d) {
		// depth + 1 to allow adding
		assert((d.depth >= 0) && (d.depth <= depth()+1));

		if(divs.empty())
			assert(d.depth == 0);
		else if(d.depth < divs.back().depth)
	       /* 
		* depth starts at zero, size from one.  resizing to d.depth
		* means that from the current div of that depth and on are
		* deleted, allowing push_back to work properly.  This is a
		* clever, ergo dangerous, way of saving an asignment, but too
		* clean to pass up
		*/
			divs.resize(d.depth);
		
		divs.push_back(d);
	}
	void add(int a_depth, const String & name, int a_num=0) {
		Division desc;
		desc.name = name;
		desc.depth = a_depth;
		desc.num = a_num;

		add(desc);
	}
	
	// returns true if the divisions contained in t are equal to those
	// contained in this, *even* if one of them has greater detail
	// I don't think I still need this functionality, but I'll keep it
	bool operator==(BasicLocation & t) {
		/*
		 * All ye who enter here, despair of comprehension
		 *
		 * true if all values compared matched, in which case
		 * std::mismatch returns a pair, the first item of which is set
		 * to its end value. B'kitzur, it works. If you don't
		 * understand it, take another look at the first line of this
		 * comment
		 * THIS IS ALSO TRUE IF ONE QUEUE IS SMALLER
		 * more general matches *all* more particular locations
		 */

		typedef typename std::deque<Division>::iterator iter;
		std::pair<iter, iter> pair;
		pair = std::mismatch(divs.begin(),divs.end(), t.divs.begin());
		return *(pair.first) == *(divs.end());
	}
};

#endif
