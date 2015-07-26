#ifndef COMMENTED_BOOK_TRAVLER
#define COMMENTED_BOOK_TRAVLER

#include <string>
#include <vector>
#include <cassert>
#include "commentGroup.h"
#include "division.h"

template<typename CharT>
class CommentedBookTraveler {
private:
	typedef CommentGroup<BasicComment<CharT> > CommentGroupT;
	typedef basic_string<CharT> SourceT;

	typedef Book<SourceT, CharT> SourceBook;
	typedef Book<CommentGroupT, CharT> CommentGroupBook;
public:
	typedef Book<SourceT, CharT>::iterator SourceIterator;
	typedef Book<CommentGroupT, CharT>::iterator CommentGroupIterator;
private:
	SourceIterator cur_source;
	SourceIterator source_end;
	std::vector<CommentGroupIterator> cur_comGroup_vector;
	void assertOnSame(int i) { assert(cur_source == cur_comGroup_vector[i]); }
	// only most particular div should have content
	bool commentOnGeneral() { return(not cur_source->hasContent()) }
public:
	/* 
	   I don't handle commentGroup in constructor because I only want to
	   use refrences, and can't vla refrences.  I could use iterators, but
	   then I might get passed iterators in random places, I want
	   particularly beginings, to keep things matched up
	 */
	CommentedBookTraveler(SourceBook & sb) { 
		cur_source = sb.begin();
		source_end = sb.end()
	}
	CommentedBookTraveler & add(CommentGroupBook & cgb) {
		cur_comGroup_vector.push_back(cgb.begin());
		return *this;
	}
	void operator++() {
		++cur_source;
		for(int i = 0; i < cur_comGroup_vector.size(); i++)
			if(*cur_source == *cur_comGroup_vector + 1)
				++cur_comGroup_vector;
		// if the next comment div is diffrent, means that its ahead
		// and the source iterator will get there later
	}

	void operator++(int) { operator++(); }
	Division<CommentGroupT, CharT> & currentCommentGroup(int i=0) {
		return *cur_comGroup_vector[i];
	}

	bool hasComment(int i = 0) {
		if(*cur_source == *cur_comGroup_vector[i])
			if(cur_comGroup_vector[i]->hasContent())
				return true;
		return false;
	}

	SourceT & source(int i = 0) {
		assert(*cur_souce == *cur_comGroup_vector[i]);
		return *cur_souce;

	}
	iterator sourceBegin(int i = 0) {
		assertOnSame(i);

		if(commentOnGeneral())
			return cur_source;
		else 
			return cur_source + 1;
	}
public:
	iterator sourceEnd(int i=0) {
		assertOnSame(i);

		int aheadToPastTheEnd = 1;
		if(not commentOnGeneral())
			return cur_source + 1;
		else {
			assert(cur_source[1].hasContent());
			assert(cur_source[1]->depth > cur_source->depth);

			int before_data_depth;
			before_data_depth = cur_souce->depth;
			
			while(cur_source + aheadToPastTheEnd != sourceEnd
					&& cur_source[aheadToPastTheEnd]->depth 
						!= before_data_depth)
				aheadToPastTheEnd++;
		}

		return cur_source + aheadToPastTheEnd;
	}
};

#endif
