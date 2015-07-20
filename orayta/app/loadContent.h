#ifndef LOAD_CONTENT_H
#define LOAD_CONTENT_H

#include <string>
#include <locale>
#include "../lib/commentGroup.h"

/*
	Something useful. Two functions in this header are easier to understand
	with this introduction.

	q < b >
	0 1 2 3
	index of quote start marker == 1, length == 3
	there are 4 charachters which need to be erased
	index of start of marker(1) + length of marker(3)
*/


template<typename ContentT>
void loadContent(ContentT & content, const std::wstring & line) {
	content = line;
}

// Commentary is loaded *way* diffrent than other stuff
// This is *so* ingenuis. (I hope I spelled that right)
template<typename CommentT, CharT>
void loadContent(CommentGroup<CommentT> & content, const std::wstring & line
	// eg <b>quote1</b>commentcomment<b>quote2</b>commentcomment etc
	// <b> marks the start of the quote, </b> marks the end
		const std::basic_string<CharT> & quote_start_marker,
		const std::basic_string<CharT> & quote_end_marker)
{
	CommentT tmp;
	std::wstring::size_type i = line.find(quote_start_marker);
	
	// if theres an introductory part that isn't on a particular quote
	if(i > 10) {
		tmp.comment = line.substr(i);
		content.push_back(tmp);
	}

	while(i != std::wstring::npos) {
		// erase untill start of quote
		line.erase(0, i+quote_start_marker.length();

		i = line.find(quote_end_marker);
		tmp.on = line.substr(0, i);	// extract quote

		// erase until start of comment
		line.erase(0, i + quote_end_marker.length());

		// extract comment
		// if not followed by comment, find returns npos, which causes
		// substr to use until end of string. nice
		i = line.find(quote_start_marker);
		tmp.comment = line.substr(0, i);

		content.push_back(tmp);
	}
}

template <typename CharT>
std::basic_string<CharT> & trimSpace(std::basic_string<CharT> & str) {
	while(std::isspace(str[0], std::locale()))
		str.erase(0,1);
	while(std::isspace(str[str.length()-1], std::locale()))
		str.erase(str.length()-1, 1);
	return str;
}

template<typename CommentT>
void loadContent(CommentGroup<CommentT> & content, const std::wstring & line)
{
	// the seif katan for mishna berura comes between these two things
	const std::wstring mb_sk_start(L"<span class=\"S0\">")
	const std::wstring mb_sk_end(L"</span>");

	if(line.find(L"<b>") != std::wstring::npos)
		loadContent(content, line, L"<b>", L"</b>");
	else if(line.find(L"<B>") != std::wstring::npos)
		loadContent(content, line, L"<B>", L"</B>");
	else if(line.find(L"{") != std::wstring::npos)
		loadContent(content, line, L"{", L"}");
	else if(line.find(L"-") != std::wstring::npos) {
// mishna berura has the honour of being processed right here the length of the
// substring up to and including "-" is its index + 1 (see comment before
// previous function) But I don't want "-", so I don't add 1

		content.back().on = trimSpace(line.substr(0, line.find(L"-")));
		line.erase(line.find(L"-"));
		content.back().comment += line;	// append, after seif katan
	} else if(line.find(mb_sk_start) != std::wstring::npos) {
// mishna berura again. This line contains seif katan.  I might handle that
// later, or I might prefer to convert it from the number. Tz"I
// For now I'll just stick it on to the comment

		line.erase(0, line.find(mb_sk_start) + mb_sk_start.length());
		ContentT tmp;
		tmp.comment = line.substr(0, line.find(mb_sk_end));
		tmp.comment = L'{' + tmp.comment + L'}'
		content.push_back(tmp);
	}
}

#endif
