#ifndef LOOSE_ON_STRING
#define LOOSE_ON_STRING

#include <string>
#include "onString.h"
#include "rangeIterator.h"

/* 
 * this class has a little bit of repetitive code which shold be looked
 * into eventually. Low priority though because readability is ok
 */
template <typename CharT>
class BasicLooseOnString : public BasicOnString<CharT>
{
private:
	typedef std::basic_string<CharT> String;
	typedef typename String::const_iterator const_iter;
	typedef RangeIterator<CharT, const_iter> IterT;
	typedef BasicOnString<CharT> Parent; // preserves sanity
	CharT lowest;
	CharT highest;
protected:
	virtual bool attach(BasicComment<CharT> & comment, const_iter search_begin)
		const;
public:
	BasicLooseOnString(String & str) : BasicOnString<CharT>(str) {}
	BasicLooseOnString(String & str, CharT a_lowest, CharT a_highest) {
		lowest = a_lowest;
		highest = a_highest;
	}
	BasicLooseOnString() {}

	void setRange(CharT a, CharT b) { lowest = a, highest = b; }
	virtual bool attach(BasicComment<CharT> & comment, 
			typename BasicOnString<CharT>::AttachMode 
				= BasicOnString<CharT>::proceed) const;
};

#include "looseOnString.cpp"

typedef BasicLooseOnString<char> LooseOnString;
typedef BasicLooseOnString<wchar_t> WLooseOnString;

#endif
