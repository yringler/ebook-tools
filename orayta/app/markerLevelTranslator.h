#ifndef MARKER_LEVEL_TRANSLATOR_H
#define MARKER_LEVEL_TRANSLATOR_H 

#include <deque>
#include <iostream>
#include <cassert>

class MarkerLevelTranslator
{
private:
	struct TranslationUnit { wchar_t marker; short level; };
	std::deque<TranslationUnit> translator;
	short m_highest;
public:
	MarkerLevelTranslator() { m_highest = -1; }
	/*					*
	 * translate between level and marker	*
	 *					*/
	wchar_t translate(short i) {
	for(std::deque<TranslationUnit>::iterator iter=translator.begin();
			iter != translator.end(); iter++)
		if(iter->level == i) return iter->marker;
	std::cout << "MarkerLevelTranslator:error\n";
	throw;
}

	short translate(wchar_t wc) {
	for(std::deque<TranslationUnit>::iterator iter=translator.begin();
			iter != translator.end(); iter++)
		if(iter->marker == wc) return iter->level;
	std::cout << "MarkerLevelTranslator:error\n";
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

	void add(wchar_t wc) { 
		assert(not exists(wc));
		m_highest++;
		TranslationUnit tmp = { wc, m_highest };
		translator.push_back(tmp);
	}
	
	short highest() { return m_highest; }
};

#endif
