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
	std::vector<CommentGroup<BasicComment<CharT> >*> commentaries;
public:
	CommentedDivision() { 
		commentaries.resize(1);
		commentaries[0] = 0;
	}

	void numCommentaries(int num) { 
		commentaries.resize(num);
		for(int i = 0; i < num; i++)
			commentaries[i] = 0;
	}

	CommentGroup<BasicComment<CharT> > & commentary(int i=0) {
		assert(commentaries[i]);
		return *commentaries[i];
	}
	CommentGroup<BasicComment<CharT> > & operator[int i] {
		return commentary(i);
	}

	bool hasCommentary() {
		for(int i=0; i < commentaries.size(); ++i)
			if(commentaries[i] != 0)
				return true;
	}

	bool hasCommentary(int i) { return commentaries[i]; }
};

#endif
