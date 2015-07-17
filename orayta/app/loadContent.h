#ifndef LOCATED_CONTENT_LOADER_H
#define LOCATED_CONTENT_LOADER_H

#include <istream>
#include <deque>
#include <string>
#include <cassert>
#include "../lib/book.h"
#include "../lib/locatedContent.h"
#include "../lib/commentGroup.h"

// translates from marker to depth
template <typename CharT>
class MarkerDictionary
{
private:
	typedef std::basic_string<CharT> string;

	String dict;	// translates
	bool marker_set;
	CharT m_title_marker;	// title not a div (see there)
	const String markers;	// valid markers
public:
	// I don't have to make it const, but why not?
	MarkerDictionary(const String & str) : markers(str) {
		marker_set = false;
	}
	bool is_marker(CharT ch) {
		return markers.find(ch) != String::npos;
	}
	bool exists(CharT marker) { 
		assert(marker != m_title_marker);
		return dict.find(marker) != String::npos;
	}
	void title_marker(CharT marker) { 
		assert(not marker_set);
		m_title_marker = marker; 
		marker_set = true;
	}
	void add(CharT marker) {
		if(!exists(marker))
			dict += marker;
	}
	int depth(CharT marker) {
		assert(exists(marker));
		return dict.find(marker);
	}
};

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
 * Creates a deque of LocatedContent
 * It loads two things:
 * 	the location
 * 	the content
 * of an entire text file
 *
 * The loading of the data is done via template, to be overloaded for diffrent
 * data types
 */

template <typename ContentT, typename CharT>
Book<ContentT, CharT> loadLocatedContentFile(
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
	ContentT content_base;

	while(std::readline(stream, line)) {
		if(string.empty())
			continue;
		else if(markerDictionary.is_marker(line[0])) {
			content_base = ContentT();

			BasicDivision<CharT> div;
			markerDictionary.add(line[0]);

			div.depth = markerDictionary.depth(line[0]);
			div.name = line.substr(2);
			
			location_construct.add(div);
		} else {
			content_base.location = location_base;
			loadContentLine(content_base, line);
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
