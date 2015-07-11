#ifndef DIVISION_H
#define DIVISION_H

#include <string>
#include <istream>

/*
 * Describes one text division in the text. For example, a chapter break,
 * section, paragraph - even a sentance could be a division, depending on what
 * you're doing.
 *
 * Depth: an int represents the depth. The deeper it is, the higher this number
 * is, the more particular it is. The physical analogy is that at the surface,
 * things look the same, and the deeper you go the more detail you get. 
 *
 * Its clumsy, but this is the best I can think of. Really, a higher number
 * being more general would be nice, but I don't want to count down from a
 * particular number - it feels kludgey. And I want a number for easy
 * comparison, and I can't think of a clever abstraction. So here we are.
 *
 * Number: eg 1 for chapter 1, etc
 *
 * Lable: eg "In which an ox falls into a pit" for chapter 1 (Generally, there
 * should be only one 1 for a given depth, but a lable could show up twice at
 * the same depth I suppose)
 */
 
Template<typename CharT>
struct BasicDivision
{ 
	typedef std::basic_string<CharT> String;
	String name; 	// eg chapter name
	int num;	// eg num of chapter
	int depth;	// depth described by this Division

	bool operator==(const BasicDivision & d) {
		return name==d.name && num==d.num && depth == d.depth;
	}
};

typedef BasicDivision<char> Division;
typedef BasicDivision<wchar_t> WDivision;

#endif
