#include <string>
#include <algorithm>
#include <iostream>
#include "../rangeIterator.h"

template<class T>
bool equal(T a, T a_end, T b, T b_end)
{
	while(*a == *b && a != a_end && b != b_end) {
		std::cout << *a << ' ' << *b << std::endl;
		++a;
		++b;
	}
	return (a == a_end && b == b_end);
}
int main()
{
	using std::string;
	string messy("ab3c45de09");
	string clean("abcde");
	

	typedef RangeIterator<string::iterator> Iter;
	Iter loose_messy(messy.begin(),messy.end(), '0','9');
	Iter loose_messy_end(messy.end(),messy.end(), '0','9');
	Iter loose_clean(clean.begin(),clean.end(), '0','9');
	Iter loose_clean_end(clean.end(),clean.end(), '0','9');

	if (std::equal(loose_messy,loose_messy_end,loose_clean)) {
	//if(equal(loose_messy, loose_messy_end, loose_clean, loose_clean_end)){
		std::cout << "Sucess!" << std::endl;
	} else {
		std::cout << "If you would see this, I probably didn't compile"
			<< " so you won't see this.\nBut not a sucess\n";
	}
}
