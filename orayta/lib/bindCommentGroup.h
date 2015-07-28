#ifndef BULK_BINDER_H
#define BULK_BINDER_H

#include <string>
#include "commentGroup.h"

template<typename BinderT, typename CharT>
void bind(BasicCommentGroup<BasicComment<CharT> > & comment, 
		const std::basic_string<CharT> & source) {
	
}

// if commentGroup on more general
// eg on chapter, and source content
// is found at paragraph div
template<typename BinderT, typename CharT, typename IterT>
void bind(BasicCommentGroup<BasicComment<CharT> > & comment,
		IterT source_begin, IterT source_end) {
}

void bind() {
	bind<BasicBinder<CharT> >();
}
void looseBind() {
	bind<BasicLooseBinder<CharT> >()
}

#endif
