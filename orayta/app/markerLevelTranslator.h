#ifndef MARKER_LEVEL_TRANSLATOR_H
#define MARKER_LEVEL_TRANSLATOR_H 

#include <deque>
#include <iostream>
#include <cassert>

class MarkerDepthTranslator
{
private:
	struct TranslationUnit { wchar_t marker; short level; };
	std::deque<TranslationUnit> translator;
public:
	/*					*
	 * translate between level and marker	*
	 *					*/
	wchar_t translate(short i) {
	for(std::deque<TranslationUnit>::iterator iter=translator.begin();
			iter != translator.end(); iter++)
		if(iter->level == i) return iter->marker;
	std::cout << "MarkerDepthTranslator:error\n";
	throw;
}

	short translate(wchar_t wc) {
	for(std::deque<TranslationUnit>::iterator iter=translator.begin();
			iter != translator.end(); iter++)
		if(iter->marker == wc) return iter->level;
	std::cout << "MarkerDepthTranslator:error\n";
	throw;
}
	/*					*
	 * find if marker or level exists 	*
	 * 					*/
	bool exists(wchar_t wc) {
	for(std::deque<TranslationUnit>::iterator iter=translator.begin();
			iter != translator.end(); iter++)
		if(iter->marker == wc) return true;
	return false;
}

	bool exists(short i) {
	for(std::deque<TranslationUnit>::iterator iter=translator.begin();
			iter != translator.end(); iter++)
		if(iter->level == i) return true;
	return false;
}

	void add(wchar_t wc, short i) { 
		assert(not exists(wc) && not exists(i));

		TranslationUnit tmp = { wc, i };
		translator.push_back(tmp);
	}
};

#endif
