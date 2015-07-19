#ifndef LOAD_CONTENT_H
#define LOAD_CONTENT_H

#include <string>
#include "../lib/commentGroup.h"

template<typename ContentT, typename CharT>
void loadContent(ContentT & content, const std::basic_string<CharT> & line) {
	content = line;
}

// Commentary is loaded *way* diffrent than other stuff
// This is *so* ingenuis. (I hope I spelled that right)
template<typename CharT>
void loadContent(BasicCommentGroup<CharT> & content,
		const std::basic_string<CharT> & line)
{
	// to be continued...
	// (maybe soon, if I don't get an answer about Kazakhstan soon)
}


#endif
