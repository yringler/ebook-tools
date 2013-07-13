#ifndef MESECHTA_H
#define MESECHTA_H

#include <fstream>
#include <deque>
#include <string>
#include "../container.h"

namespace sefer {

template<typename T>	// probably either mishna or meforash
class MishnaFile : Container<Container<T> >
{
	private:
		std::wifstream file;	// text file with the mesechta
	public:
		bool open(char *name);	// opens the mesechta file
		void nextPerek() { Container<T>::next(); }
		void nextMishna() { Container<T>::content().next(); }

		// for info on the next two methods, see mishna.h
		bool eatThru(const std::string & str) { 
			Container<T>::content().content().eatThru(str);
		}
		const std::string & regurgitate() {
			return Container<T>::content().content().regurgitate();
		}
};

}	// end namespace sefer

#endif
