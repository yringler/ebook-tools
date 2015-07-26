#ifndef DIVISION_H
#define DIVISION_H

#include <string>
#include <cassert>

/*
 * Describes one text division in the text. For example, a chapter break,
 * section, paragraph - even a sentance could be a division, depending on what
 * you're doing.
 *
 * The most specific division contains the content located at that division
 *
 * NOTE*
 * A BOOK TITLE IS NOT A DIVISION 
 * A division is how a book is divided, *not* the title.
 * This (kind of?) makes sence, and it makes things a *lot* easier.
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
 
template<typename ContentT, typename CharT>
struct Division
{ 
public:
	typedef std::basic_string<CharT> String;
	String name; 	// eg chapter name
	int num;	// eg num of chapter. optional
	int depth;	// depth described by this Division

	template<typename ArgT>
	bool operator==(const Division<ArgT, CharT> & d) {
		return name==d.name && num==d.num && depth == d.depth;
	}

private:
	bool content_set;
	ContentT m_content;
public:
	void content(ContentT & ad) {
		m_content = ad;
		content_set = true;
	}
	bool hasContent() { return content_set == true; }
	ContentT & content() { 
		// if content hasn't been set yet, assume that acessing it
		// in order to set it, so initilize to default value.
		// Obviously, it's already set to default, this is just more
		// complete code, in fitting with the class interface
		if(not has_content())
			content(ContentT());
		return m_content;
	}
	void clearContent() { content_set = false; }
};

#endif
