#include <cwctype>
#include <iostream>
#include "loader.h"
#include "header.h"

// returns 0 at EOF
template <typename LoadT, class ToT>
bool Loader<LoadT, ToT>::load()
{
	std::wstring line;
	/*
	 * What is being loaded. eg a string.  The file is copied over
	 * to a bunch of individual ones with WithFunc to ToT (eg a queue)
	 */
	LoadT load;

	// skips to first marker
	while(true) {
		if(getNextNonBlank(stream,line)) {
			if(isMarker(line[0])) 
				break;
		} else {
			return 0;
		}
	}

	do {
		if(isMarker(line[0])){
			wchar_t marker = line[0];
			if(not translator.exists(marker))
				translator.add(marker);
			ToUse toUse = getToUse(line);
			getLocationLable(line, toUse);

			load.clear();	// not needed, but clearer
			load.use(2);
			load.second()->lable = line;
			load.second()->level = translator.translator(marker);

			data.push_back(load);
	/*
	 * by reseting the temporary variable over here, if one content
	 * (eg text of a mishna between two markered lines) spans multiple
	 * lines, will be processed and added to queue correctly
	 * (I hope this comment atones for the <adjactive> design)
	 */
			load.clear();
		} else {
			if(load.active() != 1) load.use(1);
			LoadFunc(load, line);
			data.push_back(load);
		}
	} while(std::getNextNonBlank(stream,line));
}

template <typename LoadT, class ToT>
void Loader<LoadT, ToT>::getLocationLable(std::wstring & line, ToUse toUse)
{	
	do
		line.erase(0);	// also gets rid of marker
	while(std::iswspace(line[0]));

	if(toUse == last) {
		int last_dash = line.find_last_of(L'-');
		// array of char: a b - d - f g h
		// indices:	  0 1 2 3 4 5 6 7
		// [last_dash=] 4 + 1 = 5 = number of chars to erase
		line.erase(0, last_dash + 1);
	}

}

template <typename LoadT, class ToT>
ToUse Loader<LoadT, ToT>::getToUse(const std::wstring & line)
{
	assert(isMarker(line[0]));

// use is a pointer to vector which says how to use each level of marker
// if its non-null...
	if(toUse) {
		// ... make use of it
		int depth = translator.translate(line[0]);
		// this is a weird little line...
		return toUse[depth];
	} else {
		return last;
	}

}
template <typename LoadT, class ToT>
bool Loader<LoadT, ToT>::getNextNonBlank(std::wstring & str)
{
	while(std::getline(stream,str)) {
		if(not std::iswspace(str[0]))
			return 1;
	}
	return 0
}

template <typename LoadT, class ToT>
bool Loader<LoadT, ToT>::getNextMarkered(std::wstring & str)
{
	if(getNextNonBlank(str)) {
		if(std::iswspace(str[0])) {
			return 1;
		} else {
			std::cerr << "getNextMarkered:error\n";
			throw;
		}
	} else {
		return 0;
	}
}
