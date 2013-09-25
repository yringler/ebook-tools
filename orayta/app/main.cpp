#include <iostream>
#include <fstream>
#include <string>
using std::wstring;
#include <deque>
#include <cassert>

#include "../lib/comment.h"
#include "../lib/looseBinder.h"
#include "../lib/union.h"

#include "markerLevelTranslator.h"
#include "typedefs.h"
#include "loader.h"
#include "joinTools.h"

/*
 * functors to load the actual commentary or source data
 */
void loadSource(SourceText &, wstring &);
void loadCommentary(Commentary &, wstring &);

int main(int argc, char *argv[])
{
	if(argc != 3) {
		std::cout << "Usage: " << argv[0] << " source, commentary\n";
		return 1;
	}


	std::wifstream sourceFile(argv[0]);
	std::wifstream commentaryFile(argv[1]);
	assert(sourceFile.is_open() && commentaryFile.is_open());

	SourceTextQueue sourceTextQueue;
	CommentaryQueue commentaryQueue;
	JoinerQueue joinerQueue;

	load(sourceFile, sourceTextQueue, loadSource);
	load(commentaryFile, commentaryQueue, loadCommentary);

	join(joinerQueue, sourceTextQueue);
	join(joinerQueue, commentaryQueue);
}

void loadSource(SourceText & txt, wstring & src) { txt.first() = src; }

int betweenString(wstring & from, wstring & to,
		wchar_t bc, wchar_t ec, int pos)
{
	int begin = from.find(bc,pos);
	int end = from.find(ec, begin);
	begin++;	// to get to first char, which is after bc

	assert(begin != std::wstring::npos);
	to = from.substr(begin, end-begin);

	return end;
}

void loadCommentary(Commentary & commentary, wstring & src)
{
	WComment comment;
	int end;
	do {
		end = betweenString(src, comment.on, L'>', L'<', end);
		assert(end != wstring::npos);
		end = betweenString(src, comment.comment, L'>', L'<', end);

		commentary.first().push_back(comment);
	} while(end != wstring::npos);
}
