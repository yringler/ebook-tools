#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <deque>
#include <fstream>
#include <cassert>
#include "markerLevelTranslator.h"

const std::wstring markers(L"~!$^");	// list of markers - more?
// which part of marked line *to*use*. Default is last.
enum ToUse{last,all};

/*
 * LoadT: what information is beging loaded to. eg a string
 * ToT: where all the LoadTs are being stored. eg a queue (of strings)
 * marker: each thing, eg perek or mishna, has a line preceding
 * 	it with structural information eg perek 1 mishna 2.
 * 	these lines are prefaced by a "marker", one of ~!$^ 
 * 	(and maybe a few others).
 * markered line: line with a marker
 * ToUse/Section: 'markered line's often have multiple sections, where
 * 	the first will be more general and the second more specific,
 * 	eg ~Chapter 10-paragraph 5
 * 	ToUse is an enum which says which section *to use* - both, or 
 * 	only the last, most specific one.
 * 	Default behavior is to use the last one.
 * LoadFunc: takes args: LoadT, wstring
 * 	     sets up LoadT according to wstring
 */
template<typename LoadT, typename ToT=std::deque<LoadT> >
class Loader
{
public:
	typedef void (*LoadFuncPtr)(LoadT,std::wstring);
private:
	short *toUse;	// array of what to use for all levels
	std::wifstream & stream;
	ToT & data;	// the thing the file is being loaded into
	
	// function to load up LoadT (which is eg a posuk)
	LoadFuncPtr loadFunc;
	MarkerLevelTranslator translator;

	// arg is marked line. Replaces it with section lable based on
	// what its supposed to use (ie all or last
	void getLocationLable(std::wstring &, ToUse toUse);
	// returns what parts of marked line to use
	// also adds stuff to translator. sorry
	ToUse getToUse(const std::wstring &);

	// returns zero if reaches EOF
	bool getNextNonBlank(std::wstring &);

	bool isMarker(wchar_t wc) { 
		return (markers.find(wc) != std::wstring::npos);
	}
public:
	Loader(std::wifstream str, ToT & a_data,
		LoadFuncPtr funcPtr, ToUse * a_use = 0)
		: stream(str), data(a_data) , loadFunc(funcPtr) {
		toUse = a_use;
	}
	// returns 0 if reaches EOF
	bool load();
};

#include "loader.cpp"

// conveniance function, so that you don't have to actually create a loader
template<typename LoadT, typename ToT=std::deque<LoadT> >
bool load(std::wifstream & str, ToT & to,
		typename Loader<LoadT,ToT>::LoadFuncPtr funcPtr,
		ToUse * a_use = 0)
{
	Loader<LoadT,ToT> loader(str,to,a_use);
	loader.load();
}
#endif
