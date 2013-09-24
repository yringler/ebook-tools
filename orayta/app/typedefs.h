#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <vector>
#include <deque>
#include <string>
#include "../lib/looseBinder.h"
#include "location.h"
#include "../lib/union.h"

/*
 * Each union is either data or positional data
 * eg "Chapter 4", 2 (level)
 */

typedef Union<std::wstring, Location> SourceText;
// note: all the comments on one eg posuk are in one group in source file
// hence they are lumped together to be loaded in one queue
typedef Union<std::deque<WComment>, Location > Commentary;

const wchar_t aleph = L'א', tov = L'ת';
class CommentaryBinder : WLooseBinder {
	public: CommentaryBinder() : WLooseBinder(aleph, tov) {}
}
// this naming is a bit clumsy. sorry.
typedef Union<CommentaryBinder, Location> Joiner;

typedef std::deque<SourceText> SourceTextQueue;
typedef std::deque<Commentary> CommentaryQueue;
typedef std::deque<Joiner> JoinerQueue;

#endif
