#ifndef BIND_COMMENTED_DIVISION_H
#define BIND_COMMENTED_DIVISION_H

#include <string>
#include <cassert>
#include <deque>
#include "commentGroup.h"
#include "binder.h"
#include "looseBinder.h"

template<typename BinderT, typename CharT>
void bind(CommentedDivision<CharT> & comment) {
	assert(comment.hasContent());
	BinderT binder;
	for(int a=0; a < comment.numCommentaries(); ++a)
		if(comment.hasCommentary(a)) {
			binder.to(comment.content());
			for(int b = 0; b < comment[a].size(); b++)
				binder.attach(comment[a][b]);
		}
}

// if commentGroup on more general eg on chapter, and source content is found
// at paragraph div. IterT is asumed to point to CommentedDivision
template<typename BinderT, typename CharT, typename IterT>
void bind(CommentedDivision<CharT> & comment,
		IterT source_begin, IterT source_end) {
	assert(not comment.hasContent());
	BinderT binder;
	std::deque<BasicComment<CharT> > fail;

	IterT iter = source_begin;
	binder.to(iter->content());

	for(int a = 0; a < comment.numCommentaries(); ++a)
		if(comment.hasCommentary(a)) {
			for(int b = 0; b < comment[a].size(); ++b) {
				while(iter != source_end) {
					if(binder.attach(comment[a][b]))
						break;
					else {
						++iter;
						binder.to(iter->content());
					}
					assert(comment[a][b].attached());
					iter[b].push_back(comment[a][b]);
				}
			}
			// everything has been moved over to the right
			// location. Or the program has already terminated
			// following a failed assert
			comment[a].clear();
		}
}

template<typename CharT>
void bind(CommentedDivision<CharT> & comment) {
	bind<BasicBinder<CharT> >(comment);
}

template<typename CharT>
void looseBind(CommentedDivision<CharT> & comment) {
	bind<BasicLooseBinder<CharT> >(comment);
}

#endif
