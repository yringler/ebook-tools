#ifndef LOCATED_CONTENT_FILE_LOADER_H
#define LOCATED_CONTENT_FILE_LOADER_H

#include <istream>
#include "loadableLocatedContent"

/*
 * Creates a deque of LocatedContent
 * To actually load creates an instance of BasicLoadableLocatedContent
 */

// T will be a BasicLocatedContent specilization (I think thats the right word)
template <typename CharT, T>
class BasicLocatedContentFileLoader
{
};

#endif
