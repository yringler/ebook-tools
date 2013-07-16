#ifndef LINK_H
#define LINK_H

#include <string>
#include "range.h"

template<typename CharT>
class BasicLink
{
private:
	typedef std::basic_string<CharT> String;
	String m_link;
	String m_text;
	Range m_range;
public:
	BasicLink(String a_link, String a_text) { 
		link(a_link, a_text);
	}
	void link(String a_link, String a_text=String("")) {
		m_link = a_link;
		m_text = a_text;
	}
	const String & link() const { return m_link; }
	void text(const String & str) { m_text = str; }
	const String & text() const { return m_text; }

	Range & range() { return range; }
};
typedef BasicLink<char> Link;
typedef BasicLink<wchar_t> WLink;
#endif
