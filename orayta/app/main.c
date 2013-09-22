#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <cassert>

#include "../lib/comment.h"
#include "../lib/looseBinder.h"
#include "../lib/union.h"

#include "markerLevelTranslator.h"
#include "header.h"

bool good_args(int argc, char *argv[]);

/*
 * functors to load the actual commentary or source data
 */
bool loadSource(std::wstring &, std::wifstream &);
bool loadCommentary(WComment &, std::wifstream &);

int main(int argc, char *argv[])
{
	if(not good_args(argc, argv)) {
		std::cout << "Usage: " << argv[0] << " source, commentary\n";
		return 1;
	}


	std::wifstream sourceFile(argv[0]);
	std::wifstream commentaryFile(argv[1]);
	assert(sourceFile.is_open() && commentaryFile.is_open());

	std::deque<SourceText> sourceText;
	std::deque<Commentary> commentary;
	std::deque<Joiner> joiner;

	load<loadSource>(sourceText, sourceFile);
	load<loadCommentary>(commentary, commentaryFile);
	load(joiner, sourceText);
}
