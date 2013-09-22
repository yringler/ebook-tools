#ifndef UNION_H
#define UNION_H


#include <iostream>

template<typename T1, typename T2>
struct Union
{
T1 *first;
T2 *second;

private:
	short m_active;
public:
	Union() m_active(-1) { first=second=0; }
	void use(short i) {
		switch(i)
		{
		case 1: delete second, second = 0;
			first = new T1, m_active = 1;
			break;
		case 2: delete first, first = 0;
			second = new T2, m_active = 2;
			break;
		default: std::cerr << "Union.use()::error\n"; throw;
		}
	}
	short active() { return active; }
};

#endif
