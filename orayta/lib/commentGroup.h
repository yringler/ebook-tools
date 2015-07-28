#ifndef COMMENT_GROUP_H
#define COMMENT_GROUP_H

#include "comment.h"
#include <deque>

/*
 * I think this is a good idea... I really shouldn't program when I'm tired.
 * It makes a few things more conveniant:
 * 	locating. All comments really are on the same location 
 * 	loading. A single line in source could have a ton of comments, this way
 * 		I can pass them all as a single argument.
 * 	output. Probably. But I'm not thinking about that right now.
 * 	It'll definitely make it easier to keep track of the silly things,
 * 		which will make all dealings with them a bit easier
 * 	(Although I'll confess that it does feel a bit silly to make an empty
 * 	class like this.)
 */
template <typename CommentT>
class CommentGroup : public std::deque<CommentT>
{
};

#endif
