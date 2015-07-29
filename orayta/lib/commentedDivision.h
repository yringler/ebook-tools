#ifndef COMMENTED_CONTENT_H
#define COMMENTED_CONTENT_H

#include <string>
#include <vector>
#include <cassert>
#include "division.h"
#include "commentGroup.h"

template<typename CharT>
class CommentedDivision : public Division<std::basic_string<CharT>, CharT>
{
private:
	std::vector<CommentGroup<BasicComment<CharT> > > commentaries;
public:
	CommentedDivision(int i=1) { 
		commentaries.resize(i);
	}

	void numCommentaries(int num) { 
		commentaries.resize(num);
	}

	int numCommentaries() { return commentaries.size(); }

	bool hasCommentary(int i) { return not commentaries[i].empty(); }

	CommentGroup<BasicComment<CharT> > & commentary(int i=0) {
		assert(hasCommentary(i));
		return commentaries[i];
	}
	CommentGroup<BasicComment<CharT> > & operator[int i] {
		return commentary(i);
	}

	bool hasCommentary() {
		for(int i=0; i < commentaries.size(); ++i)
			if(hasCommentary(i))
				return true;
	}

};

#endif
