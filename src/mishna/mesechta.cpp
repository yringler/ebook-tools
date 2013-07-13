#include <string>
#include <iostream>
#include <cstdlib>
#include "mesechta.h"

namespace sefer {

template<typename T>
bool MishnaFile<T>::open(char *name)
{
	file.open(name);
	
	std::wstring line;	// stores a line from mesechta file
	while(std::getline(file,line)){
		if(line[0] == '^'){	// ^ marks perek in source file
			MishnaFile::add();
		} else if(line[0] == '~') {	// ~ marks line before mishna
			if(MishnaFile::empty()) {
				std::cerr << "meschta.cpp:error";
				std::exit(1);
			}
			std::getline(file,line); // this line is the mishna
			MishnaFile::front().add(line);
		}
	}
	// if something was added, return 1
	return (MishnaFile::finished() || MishnaFile::front().empty())? 0: 1;
}

}	// end namespace sefer
