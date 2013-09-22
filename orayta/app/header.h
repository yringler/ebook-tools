// misc. generic stuff
#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

/*
 * Each union is either data or positional data
 * eg "Chapter 4", 2 (level)
 */

typedef Union<std::wstring, Location> SourceText;
typedef Union<WComment, Location> Commentary;
typedef Union<WLooseBinder, Location> Joiner;

struct Location
{
	std::wstring lable;
	short level;
};

enum ToUse{last,all};

// information. section is - seperated text on marker line or 1st.
// LoadT: eg deque<string>, ie chapter
// vector<> loadSection: whether to use all sections or just one
template <class WithFunc, typename LoadT>
bool load(LoadT & data, std::wifstream & stream,
		std::vector<ToUse> * loadSection = 0);
{
}

bool load(Joiner & joiner, SourceText & sourceText);

#endif
