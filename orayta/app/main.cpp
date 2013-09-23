#include <iostream>
#include <fstream>
#include <string>
using std::wstring
#include <deque>
#include <cassert>

#include "../lib/comment.h"
#include "../lib/looseBinder.h"
#include "../lib/union.h"

#include "markerLevelTranslator.h"
#include "header.h"

/*
 * functors to load the actual commentary or source data
 */
bool loadSource(wstring &, std::wifstream &);
bool loadCommentary(Commentary &, std::wifstream &);

int main(int argc, char *argv[])
{
	if(argc != 3)
		std::cout << "Usage: " << argv[0] << " source, commentary\n";
		return 1;
	}


	std::wifstream sourceFile(argv[0]);
	std::wifstream commentaryFile(argv[1]);
	assert(sourceFile.is_open() && commentaryFile.is_open());

	SourceTextQueue sourceTextQueue;
	CommentaryQueue commentaryQueue;
	JoinerQueue joinerQueue;

	load<loadSource>(sourceTextQueue, sourceFile);
	load<loadCommentary>(commentaryQueue, commentaryFile);
	load(joinerQueue, sourceText);

	connect(joinerQueue, commentaryQueue);
}

bool loadSource(wstring & str, std::wifstream & stream)
{
	if(stream)
		return std::getline(stream,str);
	else {
		cerr << "loadSource:error\n";
		throw;
	}
}

int betweenString(wstring & from, wstring & to,
		wchar_t bc, wchar_t ec, int pos)
{
	int begin = str.find(bc,pos);
	int end = str.find(ec, begin);
	begin++;	// to get to first char, which is after bc

	assert(begin != npos);
	to = line.substr(begin, end-begin);

	return end;
}

bool loadCommentary(Commentary & commentary, std::wifstream & stream)
{
	using wstring::npos;

	int end = 0;
	wstring line;
	WComment comment;
	
	do {
		// contains all the perushim on an eg posuk
		if(not std::getline(stream,line)){
			std::cerr << "loadCommentary:error\n";
			throw;
		}

		end = betweenString(line, comment.on, L'>', L'<', end);
		assert(end != npos);
		end = betweenString(line, comment.comment, L'>', L'<', end);

		commentary.first()->push_back(comment);
	} while(end != npos);

	return 1;
}
