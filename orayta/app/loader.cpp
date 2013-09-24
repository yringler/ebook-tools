#include <cwctype>
#include <iostream>
#include "loader.h"
#include "typedefs.h"

// returns 0 at EOF
template <typename LoadT, class ToT>
bool Loader<LoadT, ToT>::load()
{
	std::wstring line;
	/*
	 * What is being loaded. eg a string.  The file is copied over
	 * to a bunch of individual ones with WithFunc to ToT (eg a queue)
	 */
	LoadT tmp;

	// skips to first marker
	while(true) {
		if(getNextNonBlank(line)) {
			if(isMarker(line[0])) 
				break;
		} else {	// if reached EOF
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

			tmp.clear();
			tmp.use(2);
			tmp.second()->lable = line;
			tmp.second()->level = translator.translate(marker);

			data.push_back(tmp);
	/*
	 * by reseting the temporary variable over here, if one content
	 * (eg text of a mishna between two markered lines) spans multiple
	 * lines, will be processed and added to queue correctly
	 * (I hope this comment atones for the <adjactive> design)
	 */
			tmp.clear();
		} else {
			if(tmp.active() != 1) tmp.use(1);
			LoadFunc(tmp, line);
			data.push_back(tmp);
		}
	} while(std::getNextNonBlank(line));
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
		// last_dash=4, + 1 = 5 = number of chars to erase
		line.erase(0, last_dash + 1);
	}
}

template <typename LoadT, class ToT>
ToUse Loader<LoadT, ToT>::getToUse(const std::wstring & line)
{
	assert(isMarker(line[0]));

// toUse is a pointer to int which says how to use each level of marker
// if its non-null...
	if(toUse) {
		// ... make use of it
		int depth = translator.translate(line[0]);
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
