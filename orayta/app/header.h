// misc. generic stuff
#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <deque>
#include <string>

// tells program where he is in the file, like a sign post
// eg "now your at a level 3 labled 'homeward bound'"
struct Location
{
	std::wstring lable;
	short level;
};

/*
 * Each union is either data or positional data
 * eg "Chapter 4", 2 (level)
 */

typedef Union<std::wstring, Location> SourceText;
// note: all the comments on one eg posuk are in one group in source file
// hence they are lumped together to be loaded in one queue
typedef Union<std::deque<WComment>, Location > Commentary;
typedef Union<WLooseBinder, Location> Joiner;

typedef std::deque<SourceText> SourceTextQueue;
typedef std::deque<Commentary> CommentaryQueue;
typedef std::deque<Joiner> JoinerQueue;

void connect(Joiner & joiner, Commentary & commentary);

#endif
