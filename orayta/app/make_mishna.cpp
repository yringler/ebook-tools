#include <iostream>
#include <fstream>
#include <string>
#include <deque>

#include "../lib/comment.h"
#include "../lib/looseBinder.h"
#include "../lib/labled.h"

/*
 * args: mishna.txt bartenura.txt
 */

template<typename CharT>
bool getLineStartingWith(char, const std::basic_string<CharT> &);

template<typename CharT>
std::basic_string<CharT> getWordsFrom(int, const std::basic_string<CharT> &);

int main(int argc, char *argv[])
{
	if(argc != 3) {
		std::cerr << "Usage: " << *argv << " mishna.txt bartenura.txt";
		std::cerr << std::endl;
		return 1;
	}

	std::wifstream mishna(argv[1]);
	std::wifstream bartenura(argv[2]);

	if(not mishna.is_open() || not bartenura.is_open()) {
		std::cerr << "Error:a file failed to open\n";
		return 1;
	}

	using std::wstring;
	using std::deque;
	
	// typedefs for mishna
	typedef Labled<wstring> Mishna;
	typedef Labled<deque<Mishna> > Perek;
	typedef Labled<deque<Perek> > Mesechta;
	
	// typedefs for bartenura
	typedef Labled<WComment> Perush;
	typedef Labled<deque<Perush> >	PerushPerek;
	typedef Labled<deque<PerushPerek> > PerushMesechta;

	wstring mesechta;
	wstring perek;
	wstring mishna;
	while(getLineStartingWith('$',line)) {
		line = getWordsFrom(3,line);
		while(getLineStartingWith('^', line
	}
}
