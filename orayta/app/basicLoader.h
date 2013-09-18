#ifndef BASIC_LOADER_H
#define BASIC_LOADER_H

#include <string>
#include <iostream>
#include "markers.h"
#include "tmpStringException.h"

template<typename CharT>
bool extractFrom(int, std::basic_string<CharT> &, std::basic_istream<CharT> &);

template<typename CharT>
bool findMarker(char, std::basic_istream<CharT> &);

/*
 * template arguments:
 * 	the number of the space-defined word to start lable extract from
 * 		0 is marker of what I'm loading
 * 	marker of what is contained(ie one of !@#$~ {etc?} )
 * 	char type that will be loaded
 * 	type to add - eg mishna is type to add for perek
 * 	function to load up the add-type:
 * 		args: 	refrence to the instance to be set
 * 			file to load from
 * 	type to copy AddT to - must have a push_back() function
 */

template<int loadFrom, char childMarker,
	typename AddT, typename loadFunction, typename CharT,typename ToT>
bool basicLoader(ToT & to, std::basic_istream<CharT> & stream)
{
	extractFrom(loadFrom, to.lable, stream);	// set name
	
	AddT tmp;
	while(findMarker(childMarker, stream)) {
		tmp = AddT();	// clear tmp

		if(loadFunction(stream, tmp))
			to.push_back(tmp);
		else 
			return is_marker( (char) stream.peek() );
	}
}

template<typename CharT>
bool extractFrom(int start, std::basic_string<CharT> & to,
		std::basic_istream<CharT> & stream)
{
	tmpStringException change(stream);
	for(int i=0; i < start; i++) {
		if(not stream >> to){	// reads from non-space until space
			std::cerr << "extractFrom:err. eof?" << stream.eof();
			return 0;
	}

	if(not std::getline(stream, to)) {
		std::cerr << "extractFrom:err. eof?" << stream.eof();
		return 0;
	}
	
	return 1;
}

template<typename CharT>
bool findMarker(char marker, std::basic_istream<CharT> & stream)
{
	tmpStringException change(stream);
	std::basic_string<CharT> line;
	do {
		char next = (char) stream.peak();
		if(next == marker)
			return 1;
		else
			std::getline(stream,line);
	} while(is_marker(next));

	return 0;
}

#endif
