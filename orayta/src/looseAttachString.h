#ifndef LOOSE_ATTACH_STRING_H
#define LOOSE_ATTACH_STRING_H

#include <string>
#include "attachString.h"
#include "rangeIterator.h"

/* 
 * this class has a little bit of repetitive code which shold be looked
 * into eventually. Low priority though because readability is ok
 */
template <typename CharT>
class BasicLooseAttachString : public BasicAttachString<CharT>
{
private:
	typedef std::basic_string<CharT> String;
	typedef typename String::const_iterator const_iter;
	typedef RangeIterator<CharT, const_iter> IterT;
	typedef BasicAttachString<CharT> Parent; // preserves sanity
	CharT lowest;
	CharT highest;
protected:
	virtual bool attach(BasicLink<CharT> & link, const_iter search_begin)
		const;
public:
	BasicLooseAttachString(String & str) : BasicAttachString<CharT>(str) {}
	BasicLooseAttachString(String & str, CharT a_lowest, CharT a_highest) {
		lowest = a_lowest;
		highest = a_highest;
	}
	BasicLooseAttachString() {}

	void setRange(CharT a, CharT b) { lowest = a, highest = b; }
	virtual bool attach(BasicLink<CharT> & link, 
			typename BasicAttachString<CharT>::AttachMode 
				= BasicAttachString<CharT>::proceed) const;
};

#include "looseAttachString.cpp"

typedef BasicLooseAttachString<char> LooseAttachString;
typedef BasicLooseAttachString<wchar_t> WLooseAttachString;

#endif
