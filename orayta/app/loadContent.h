#ifndef LOCATED_CONTENT_LOADER_H
#define LOCATED_CONTENT_LOADER_H

#include <istream>
#include <deque>
#include <string>
#include <cassert>
#include "../lib/book.h"
#include "../lib/locatedContent.h"
#include "../lib/commentGroup.h"
#include "markerDictionary.h"

template<typename ContentT, typename CharT>
void loadContentLine(ContentT & content, std::basic_string<CharT> line) {
	content = line;
}

// Commentary is loaded *way* diffrent than other stuff
// This is *so* ingenuis. (I hope I spelled that right)
template<typename CharT>
void loadContentLine(BasicCommentGroup<CharT> & content,
		std::basic_string<CharT> line);

/*
 * It loads two things the location and content of an entire text file
 * The loading of the data is done via template, so there can be diffrent
 * loading methods for diffrent data types
 */

template <typename ContentT, typename CharT>
void loadLocatedContentFile(
		Book<LocatedContent<ContentT>, CharT> & book,
		const std::basic_istream<CharT> & stream,
		const std::basic_string<CharT> & markers)
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

	// every time a division is reached, its added to location_base
	// it doesn't keep on going deeper and deeper, because Location knows
	// to clear deeper info. See there for more info.
	BasicLocation<CharT> location_base;
	// in case content is spread over a few lines
	// cleared whenever a marker is reached
	LocatedContent<ContentT> locatedContent_base;
	bool working_on_content = false;

	while(std::readline(stream, line)) {
		if(string.empty())
			continue;
		else if(markerDictionary.is_marker(line[0])) {
			if(working_on_content) {
				working_on_content = false;
				book.push_back(locatedContent_base);
				locatedContent_base = ContentT();
			}

			BasicDivision<CharT> div;
			markerDictionary.add(line[0]);

			div.depth = markerDictionary.depth(line[0]);
			div.name = line.substr(2);
			
			location_construct.add(div);
		} else {
			if(not working_on_content) {
				working_on_content = true;
				locatedContent_base.location = location_base;
			}

			loadContentLine(locatedContent_base, line);
		}
	}
}

template<typename CharT>
void loadContentLine(BasicCommentGroup<CharT> & content,
		std::basic_string<CharT> line)
{
	// to be continued...
	// (maybe soon, if I don't get an answer about Kazakhstan soon)
}

#endif
