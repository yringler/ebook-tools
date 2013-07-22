#include <fstream>
#include <string>
#include "../linkableString.h"

int main()
{
	std::ifstream story("story");
	std::ifstream comments("comments");
	LinkableString commented_story;

	// load story
	std::string tmp_str;
	while(std::getline(story,tmp_str)){
		commented_story += tmp_str;
	}

	// add comments
	Link tmp_link;
	while(std::getline(comments,tmp_str)){
		if(tmp_str[0] == '~'){
			tmp_link.link = tmp_str.substr(1);
			std::getline(comments,tmp_str);
			tmp_link.text = tmp_str;
			commented_story.addLink(tmp_link);
		}
	}
}
