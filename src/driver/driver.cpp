#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iterator>
#include "../link.h"
#include "../attachString.h"

int main()
{
	using std::cout;
	using std::endl;

	AttachString commentedStory;
	std::queue<Link> commentQueue;

	cout << "INITIALIZING DATA\n\n";

	std::ifstream story("story.txt");
	std::ifstream comments("comments.txt");
	if(story.is_open() && comments.is_open())
		cout << "Files opened\n";
	else
		cout << "Files not opened\n";

		/* load story */
	std::string one_line;
	std::string all_lines;
	while(std::getline(story,one_line)){
		all_lines += one_line;
	}

	commentedStory = all_lines;

		/* load comments */
	Link tmp_link;
	std::string tmp_str;
	while(std::getline(comments,tmp_str)){
		if(tmp_str[0] == '~'){
			tmp_link.link = tmp_str.substr(1);
			std::getline(comments,tmp_str);
			tmp_link.text = tmp_str;
		
			cout << "Attempt attach...";
			if(commentedStory.attach(tmp_link)) {
				cout << "Attached\n";
				commentQueue.push(tmp_link);
			} else {
				cout << "Failed\n";
			}
		}
	}

	cout << "\nENTERED PROCCESSING LOOP\n\n";

	if(commentQueue.empty()) {
		cout << "Error:commentQueue empty\n";
		return 1;
	}

		/* Print story with comments */
	std::ostream_iterator<char> p_iter(cout);
	std::copy(commentedStory.get().begin(), commentQueue.front().begin, 
			p_iter);

	Link next_link = commentQueue.front();
	while(not commentQueue.empty()) {
		tmp_link = next_link;
		commentQueue.pop();

		std::copy(tmp_link.begin, tmp_link.end, p_iter);
		cout << "<comment>" << tmp_link.text << "<\\comment>";
		if(not commentQueue.empty()) {
			next_link = commentQueue.front();
			std::copy(tmp_link.end, next_link.begin, p_iter);
		} else {
			std::copy(tmp_link.end, commentedStory.get().end(), 
					p_iter);
		}
	}

	cout << endl;
}
