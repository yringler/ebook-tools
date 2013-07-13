#ifndef SOURCE_TEXT_H
#define SOURCE_TEXT_H

#include <string>
#include "component.h"

namespace sefer {

class SourceText : public Component
{
	private:
		std::wstring eaten;	// section to print
		int ate_thru;	// index of last charachter eaten
	public:
		SourceText(std::wstring str, int i) : Component(str,i) {
			ate_thru = 0;
		}

// dry facts:
// 	"eat" means save and remove from access
// 		(at least thru usage of the eat/regurgitate concept)
// 	eats from first char of uneaten text thru (found) search string
// 	returns 1 if search string is found, 0 on failure
// intended usage: search for d"h
		bool eatThru(const std::wstring & search);
		const std::wstring regurgitate();
		void undoEating() { ate_thru = 0, eaten.clear(); }
};

}	// end namespace sefer
#endif
