#ifndef LOAD_H
#define LOAD_H

#include <vector>

// vector<> loadSection: where on marker line to start extracting location
// information. section is - seperated text on marker line or 1st.
// LoadT: eg deque<string>, ie chapter
template <typename LoadT, class WithFunc>
bool load(std::vector<short> & loadSection, LoadT & data,
		std::wifstream & stream)
{
}

#endif
