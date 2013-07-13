#ifndef SEFER_COMPONENT_H
#define SEFER_COMPONENT_H

#include <string>

namespace sefer {

class Component {
private:
	int m_num;	// could be perek number, mishna number, etc
	std::wstring m_text;	// could be "Noach", mishna text, etc
public:
	/* Depending on what sourt of component it is
	 * number or text could be more important and logically first */
	Component(int i = 0, std::wstring str = std::wstring()) {
		m_num = i;
		m_text = str;
	}
	Component(std::wstring str, int i = 0){
		m_text = str;
		m_num = i;
	}

	void num(int i) { m_num= i; }
	int num() { return m_num; }
	void text(std::wstring & str) { m_text = str; }
	std::wstring & text() { return m_text; }
};

}	// end namespace sefer

#endif
