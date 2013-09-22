#ifndef LOAD_H
#define LOAD_H

#include <vector>

// vector<> from: where on marker line to start extracting location information
// 	from[0] for level 0, etc
// LoadT: eg deque<string>, ie chapter
template <typename LoadT, class WithFunc>
bool load(std::vector<short> & loadFrom, LoadT & data, std::wifstream &)
{
}

#endif
