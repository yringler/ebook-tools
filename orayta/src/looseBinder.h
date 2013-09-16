#ifndef LOOSE_BINDER
#define LOOSE_BINDER

#include <string>
#include "binder.h"
#include "rangeIterator.h"

/* 
 * this class has a little bit of repetitive code which shold be looked
 * into eventually. Low priority though because readability is ok
 */
template <typename CharT>
class BasicLooseBinder : public BasicBinder<CharT>
{
private:
	typedef std::basic_string<CharT> String;
	typedef typename String::const_iterator const_iterator;
	typedef BasicBinder<CharT> Parent; // preserves sanity

	CharT lowest;
	CharT highest;
protected:
	virtual bool attach(BasicComment<CharT> & comment,
			const_iterator search_begin) const;
public:
	void setRange(CharT a, CharT b) { lowest = a, highest = b; }

	BasicLooseBinder(String & str, CharT a = CharT(), CharT b = CharT())
		: BasicBinder<CharT>(str) { setRange(a, b); }

	BasicLooseBinder(const_iterator ia, const_iterator ib,
			CharT ca = CharT(), CharT cb = CharT())
		: BasicBinder<CharT>(ia,ib) { setRange(ca, cb); }

	BasicLooseBinder(CharT a = CharT(), CharT b = CharT())
		{ setRange(a, b); }

	virtual bool attach(BasicComment<CharT> & comment, 
			typename BasicBinder<CharT>::AttachMode 
				= BasicBinder<CharT>::next) const;
};

#include "looseBinder.cpp"

typedef BasicLooseBinder<char> LooseBinder;
typedef BasicLooseBinder<wchar_t> WLooseBinder;

#endif
