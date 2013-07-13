#include <iostream>
#include <cstdlib>
#include "source_text.h"

namespace sefer {

bool SourceText::eatThru(const std::wstring & search) {
	// index where first char of search string was found
	int found_start = Component::text().find(search,ate_thru);
	if(found_start == std::string::npos) return 0;	// if didn't find

	/* to find amount of extra (ie not part of search) text being added 
	   ex: "abcdef".eatThru(c): "ab" is extra */
	int last_skipped = found_start - 1;	// last extra char
	int num_skipped = last_skipped - ate_thru;
	int size_add = num_skipped + search.size();

	eaten.append(text(),ate_thru+1,size_add);
	ate_thru += size_add;

	return 1;
}

const std::wstring SourceText::regurgitate()
{
	if(not eaten.empty()){
		std::wstring tmp(eaten);
		eaten.clear();
		return tmp;
	} else {
		std::cerr << "content.cpp:error";
		exit(1);
	}
}

}	// end namespace sefer
