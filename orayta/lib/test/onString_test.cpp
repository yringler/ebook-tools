#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iterator>
#include <algorithm>
#include "../comment.h"
#include "../binder.h"

int main()
{
	using std::cout;
	using std::endl;

	Binder binder;
	std::queue<Comment> commentQueue;

	cout << "INITIALIZING DATA\n\n";

	std::ifstream story("story.txt");
	std::ifstream comment_file("comments.txt");
	if(story.is_open() && comment_file.is_open())
		cout << "Files opened\n";
	else
		cout << "Files not opened\n";

		/* load story */
	std::string one_line;
	std::string all_lines;
	while(std::getline(story,one_line)){
		if(not all_lines.empty())
			all_lines += ' ';
		all_lines += one_line;
	}

	binder.to(all_lines.begin(), all_lines.end());

		/* load comments */
	Comment tmp_comment;
	std::string tmp_str;
	while(std::getline(comment_file,tmp_str)){
		if(tmp_str[0] == '~'){
			tmp_comment.on = tmp_str.substr(1);
			std::getline(comment_file,tmp_str);
			tmp_comment.comment = tmp_str;
		
			cout << "Attempt attach...";
			if(binder.attach(tmp_comment)) {
				cout << "Attached\n";
				commentQueue.push(tmp_comment);
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
	std::copy(binder.begin(), commentQueue.front().begin, p_iter);

	Comment next_comment = commentQueue.front();
	while(not commentQueue.empty()) {
		tmp_comment = next_comment;
		commentQueue.pop();

		std::copy(tmp_comment.begin, tmp_comment.end, p_iter);
		cout << "<comment>" << tmp_comment.comment << "<\\comment>";
		if(not commentQueue.empty()) {
			next_comment = commentQueue.front();
			std::copy(tmp_comment.end, next_comment.begin, p_iter);
		} else {
			std::copy(tmp_comment.end, binder.end(), p_iter);
		}
	}

	cout << endl;
}
