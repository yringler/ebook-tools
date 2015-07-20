#ifndef LOAD_CONTENT_H
#define LOAD_CONTENT_H

#include <string>
#include "../lib/commentGroup.h"

template<typename ContentT>
void loadContent(ContentT & content, const std::wstring & line) {
	content = line;
}

// Commentary is loaded *way* diffrent than other stuff
// This is *so* ingenuis. (I hope I spelled that right)
template<typename CommentT>
void loadContent(CommentGroup<CommentT> & content, const std::wstring & line)
{
	// eg <b>quote1</b>commentcomment<b>quote2</b>commentcomment etc
	// quotes 1 and 2 are the quotes from source text that are being
	// commented on
	// and <b> and </b> are the markers, or marks
	// I don't use <b> etc because sometimes its <B>
	
	// start of chars which mark that a quote is coming
	std::wstring quote_mark_start(L"<");	

	std::wstring before_quote_start(L">");
	std::wstring after_quote_end(L"</");	
	
	std::wstring before_comment_start(L">")

	WComment tmp;
	std::wstring::size_type i = line.find(before_quote_start);
	
	// if theres an introductory part, not on a particular quote
	if(i > 10) {
		tmp.comment = line.substr(line.find(quote_mark_start));
		content.push_back(tmp);
	}

	while( (i = line.find(before_quote_start)) != std::wstring::npos) {
		// +1 because index starts at 0, and length starts at 1
		line.erase(0, i+1);

		// not +1, because I don't want that '<' also
		tmp.on = line.substr(0, line.find(after_quote_end);	

		line.erase(0, line.find(before_comment_start) + 1);

		// if not followed by comment, find returns npos, which causes
		// substr to use untill end of string. nice
		tmp.comment = line.substr(0, line.find(quote_mark_start));

		content.push_back(tmp);
	}
}

#endif
