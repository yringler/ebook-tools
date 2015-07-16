#ifndef LOCATED_CONTENT_FILE_LOADER_H
#define LOCATED_CONTENT_FILE_LOADER_H

#include <istream>
#include <deque>
#include <string>
#include <cassert>
#include "../lib/locatedContent.h"

// translates from marker to depth
template <typename CharT>
class MarkerDictionary
{
private:
	std::basic_string<CharT> markers;
public:
	bool exists(CharT marker) { 
		return markers.find(marker) != std::basic_string<CharT>::npos;
	}
	void add(CharT marker) {
		if(!exists(marker))
			markers += marker;
	}
	int depth(CharT marker) {
		assert(exists(marker));
		return markers.find(marker);
	}
};

template<typename LocatedContentT, typename CharT>
defaultLocatedContentLoader(const std::basic_string<CharT> & line,
		LocatedContentT & locatedContent) {
	locatedContent = line;
}
/*
 * Creates a deque of LocatedContent
 * It loads two things:
 * 	the location
 * 	the content
 * of an entire text file
 *
 * The loading of the data is done via template based functor ContentLoader()
 */

template <typename LocatedContentT, typename LocatedContentLoader =
	defaultLocatedContentLoader<LocatedContentLoader, CharT>,
	typename CharT>
loadLocatedContentFile(const std::basic_istream<CharT> & stream,
		const std::basic_string<CharT> & markers)
{
	std::deque<LocatedContentT> locatedContentQueue;
	MarkerDictionary<CharT> markerDictionary;
}

#endif
