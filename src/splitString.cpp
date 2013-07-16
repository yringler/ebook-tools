#include "splitString.h"


template<typename CharT>
bool BasicSplitString<CharT>::next()
{
	if(noNext()) return 0;

		/* set range start */
	// finish() is the char *before* delimiter
	// it would work to add 1, but to be logically consistent add 2
	range.start(findDelim(range.finish()) + 2);
	// passes over consecutive delimiters
	while(m_delimiters.find(m_string[range.start()]))
		range.start(range.start() + 1);

		/* set range end */
	// if there are no more delimiters
	if(findDelim(range.start()) == String::npos) {
		range.finish(m_string.length());
	} else {
	// subtract 1 so that last charachter is not delimiter
		range.finish(findDelim(range.start()) - 1);
	}
}
