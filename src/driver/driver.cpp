#include <iostream>
#include <fstream>
#include <string>
#include "../linkableString.h"

int main()
{
	using std::cout;
	using std::endl;

	cout << "INITIALIZING DATA\n\n";

	std::ifstream story("story.txt");
	std::ifstream comments("comments.txt");
	if(story.is_open() && comments.is_open())
		cout << "Files opened\n";
	else
		cout << "Files not opened\n";
	LinkableString commented_story;

	// load story
	std::string tmp_str;
	while(std::getline(story,tmp_str)){
		commented_story += tmp_str;
		cout << "Section: " << tmp_str;
	}
	cout << commented_story;

	// add comments
	Link tmp_link;
	while(std::getline(comments,tmp_str)){
		if(tmp_str[0] == '~'){
			tmp_link.link = tmp_str.substr(1);
			std::getline(comments,tmp_str);
			tmp_link.text = tmp_str;

			cout << "Attempt add...";
			if(commented_story.addLink(tmp_link)){
				cout << "Added\n";
				cout << "Body: " << tmp_link.text << endl;
				cout << "Range: " << tmp_link.range.start 
					<< ' ' << tmp_link.range.finish
					<< endl;
			} else
				cout << "Fail\n";
		}
	}

	commented_story.start();
	cout << "\nENTERED PROCCESSING LOOP\n\n";
	while(not commented_story.finished()){
		cout << commented_story.curStr();

		if(commented_story.hasLink())
			cout << "<link>" 
				<< commented_story.link().text
				<< "<\\link>";
		commented_story.next();
	}
	cout << commented_story.curStr();
	if(commented_story.hasLink())
		cout << "<link>" << commented_story.link().text << "<\\link>";
	cout << endl;
}
