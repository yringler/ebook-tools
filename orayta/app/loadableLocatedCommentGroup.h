#ifndef LOADABLE_LOCATED_COMMENT_GROUP
#define LOADABLE_LOCATED_COMMENT_GROUP

#include "loadableLocatedContent.h"
#include "../src/commentGroup.h"

template <typename CharT>
class BasicLoadableLocatedCommentGroup : 
	public BasicLoadableLocatedContent< CharT, CommentGroup<CharT> >
{
public:
	BasicLoadableLocatedCommentGroup & operator=(
			const std::basic_string<CharT> & line) {
		// To be continued ...
		return *this;
	}
};

#endif
