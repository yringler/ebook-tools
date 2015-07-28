#ifndef COMMENTED_BOOK_H
#define COMMENTED_BOOK_H

#include <string>
#include <vector>
#include "book.h"
#include "commentedDivision.h"
#include "bulkBinder.h"
#include "binder.h"
#include "looseBinder.h"

template<typename CharT>
class CommentedBook : public Book<CommentedDivision<CharT> >
{
private:
	typedef Book<std::basic_string<CharT>,CharT> SourceBook;
	typedef Book<BasicComment<CharT>, CharT> CommentBook;
	std::vector<std::basic_string<Chart> > commentaryTitles;
	const int numCommentaries;
	int num_added;

public:
	CommentBook(SourceBook & sb, int nc = 1) : numCommentaries(nc) {
		for(SourceBook::iterator iter = sb.begin(); iter != sb.end(); iter++) {
			push_back(*iter);
			back().numCommentaries(nc);
		}
		commentaryTitles.resize(numCommentaries);
		cur_com_index = 0;
	}

	CommentedBook & add(CommentBook & cb) {
		commentaryTitles[cur_com_index] = cb.title();
		++cur_com_index

		iterator s_iter = begin();
		CommentBook::iterator c_iter = cb.begin();

		while(csi != end() && cb_iter != cb.end()) {
			if(*csi == *cb_iter) {
				if cb_iter->hasContent()
					csi->commentary(i) = *csi;
				++cb_iter;
			}
			++csi;
		}
	}

	std::basic_string<CharT> & title(int i=0) { return commentaryTitles[i]; }

	template<typename BinderT>
	void bind() {
		for(iterator iter = begin(); iter != end(); ++iter)
			for(int i=0; i < numCommentaries; ++i)
				if(iter->hasCommentary(i))
					if(iter->hasContent()) {
					}
					// if commentGroup on more general
					// eg on chapter, and source content
					// is found at paragraph div
					else {
					}
	}

	void bind() {
		bind<BasicBinder<CharT> >();
	}
	void looseBind() {
		bind<BasicLooseBinder<CharT> >()
	}
};

#endif
