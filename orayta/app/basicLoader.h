/*
 * dude exceptions are totally awesome!!!
 * I hope this works...
 */
#ifndef BASIC_LOADER_H
#define BASIC_LOADER_H

#include <string>
#include <iostream>
#include <cctype>

#include "tmpStreamException.h"

// pulls out nth and on whitespace seperated word from string
template<typename CharT>
bool extractFrom(int, std::basic_string<CharT> &, std::basic_istream<CharT> &);

// carefull not to remove non-empty lines from stream
template<typename CharT>
bool skipEmptyTillMarker(char, std::basic_istream<CharT> &);

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

// returns 1 if loaded something, 0 if not
template<int loadFrom, char childMarker,
	typename AddT, typename loadFunction, typename CharT,typename ToT>
bool basicLoader(ToT & to, std::basic_istream<CharT> & stream)
{
	extractFrom(loadFrom, to.lable, stream);	// set name
	
	int orig_size = to.size();
	AddT tmp;

	try {
		// keeps on loading more stuff untill doesn't find child marker
		while(skipEmptyTillMarker(childMarker, stream)) {
			tmp = AddT();	// clear tmp

			if(loadFunction(stream, tmp))
				to.push_back(tmp);
			else {
		// catches a problem - I already skipped till right marker
		// so it should have worked
				std::cerr << "basicLoader:problem\n";
				throw;
			}
		}
	} catch(std::ios_base::failure &) {
		using std::ios_base;
		switch(std::cin.rdstate())
		{
			case ios_base::badbit:
			case ios_base::failbit:
				std::cerr << "loader:oh boy\n";
				throw;
			case ios_base::eofbit:
				break;
		}
	}

	return (orig_size < to.size());
}

template<typename CharT>
bool extractFrom(int start, std::basic_string<CharT> & to,
		std::basic_istream<CharT> & stream)
{
	TmpStreamException<CharT> change(stream);

	for(int i=0; i < start; i++)
		stream >> to;	// reads from non-space until space
	std::getline(stream, to);

	return (not to.empty());
}

template<typename CharT>
bool skipEmptyTillMarker(CharT marker, std::basic_istream<CharT> & stream)
{
	TmpStreamException<CharT> change(stream);

	std::basic_string<CharT> line;

// I'm a little nervous of that test - what if the 2nd char is not a space?
// but I can't imagine that that will happen...
// also, the (char) , there for if line is wide...
	while(std::isspace((char)stream.peek())) {
		std::getline(stream,line);
	}
	return (stream.peek() == marker);
}

#endif
