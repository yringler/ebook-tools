#ifndef UNION_H
#define UNION_H

#include <iostream>

template<typename T1, typename T2>
class Union
{
private:
	T1 *m_first;
	T2 *m_second;
	short m_active;
public:
	Union() : m_active(-1) { m_first=m_second=0; }
	void clear() {
		delete m_first, delete m_second;
		m_first = m_second = 0;
		m_active = -1;
	}
	void use(short i) {
		switch(i)
		{
		case 1: clear();
			m_first = new T1, m_active = 1;
			break;
		case 2: clear();
			m_second = new T2, m_active = 2;
			break;
		default: std::cerr << "Union.use()::error\n"; throw;
		}
	}
	short active() { return m_active; }
	T1 & first() { return *m_first; }
	T2 & second() { return *m_second; }
};

#endif
