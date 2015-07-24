#ifndef LOCATED_CONTENT_LOADER_H
#define LOCATED_CONTENT_LOADER_H

#include <istream>
#include <deque>
#include <string>
#include <cassert>
#include "../lib/book.h"
#include "../lib/division.h"
#include "loadContent.h"
#include "markerDictionary.h"

/*
 * It loads two things the location and content of an entire text file
 * The loading of the data is done via template, so there can be diffrent
 * loading methods for diffrent data types
 */

template <typename ContentT, typename CharT, typename LoaderFunc>
void loadBook(
		Book<Division<ContentT, CharT> > & book,
		const std::basic_istream<CharT> & stream,
		const std::basic_string<CharT> & markers,
		// support custom function for unique formatting. But the
		// default supports everything that I saw (this is some pretty
		// wild template stuff. But it should work)
		LoaderFunc loaderFunc = loadContent<ContentT>)
{
	MarkerDictionary<CharT> markerDictionary(markers);
	std::basic_string<CharT> line;	// line being processed now from file

	// this could probably be made a one liner, but this is easier
	while(std::readline(stream, line)) {
		if(markerDictionary.is_marker(line[0])) {
			markerDictionary.title_marker(line[0]);
			// I'm pretty sure theres always one ' 'after the marker
			book.title = line.substr(2);
			break;
		}
	}

	// tmp_div is only cleared when a division is reached, allowing content to be
	// spread out over multiple lines
	Division<ContentT,CharT> tmp_div

	while(std::readline(stream, line)) {
		if(string.empty())
			continue;
		else if(markerDictionary.is_marker(line[0])) {
			BasicDivision<CharT> div;
			markerDictionary.add(line[0]);

			div.depth = markerDictionary.depth(line[0]);
			div.name = line.substr(2);
			div.clearContent();

			book.push_back(div);
		} else {
			loaderFunc(book.back().content(), line);
		}
	}

	cassert(not book.empty());
}

#endif
