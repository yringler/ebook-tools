#ifndef SPLIT_STRING_H
#define SPLIT_STRING_H

#include <string>
#include <deque>
#include "range.h"

template<typename CharT>
class BasicSplitString
{
	private:
		typedef std::basic_string<CharT> String;
		String m_string;
		String m_delimiters;
		Range range;	// begining and finish of current split
		int findDelim(int start) { 
			return m_string.find_first_of(m_delimiters, start);
		}
	public:
		BasicSplitString(const String & str, const String & del) 
			: m_string(str), m_delimiters(del) {}
		// returns string section from index to delimiter
		const String & part() const {
			int part_length = range.finish() - range.start() + 1;
			return m_string.substr(range.start(),part_length);
		}	
		bool next(); // sets range to next split
		bool noNext() { 
			return findDelim(range.finish()) == String::npos;
		}
		void restart() { range = Range(); }
		int index() const { return range.start(); }
		void string(const String & str) { 
			m_string = string;
			restart();
		}
		void delimiters(const String & str) { m_delimiters = str; }
};

#endif
