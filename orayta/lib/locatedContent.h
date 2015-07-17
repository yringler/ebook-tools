#ifndef LOCATED_CONTENT_H
#define LOCATED_CONTENT_H

#include "division.h"

// CharT for location type, T is content type.
// For me it'll be either comment or text
template<typename CharT, typename T>
class LocatedContent : public T
{
public:
	BasicDivision<CharT> division;
};

#endif
