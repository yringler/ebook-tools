#ifndef TMPSTREAMEXCEPTION
#define TMPSTREAMEXCEPTION

#include <ios>

template <typename CharT>
class TmpStreamException
{
private:
	short original_setting;
	std::basic_ios<CharT> & info;
public:
	TmpStreamException(std::basic_ios<CharT> & a_info) : info(a_info)
	{
		using std::ios_base;
		original_setting = info.exceptions();
		info.exceptions(ios_base::badbit | ios_base::eofbit 
				| ios_base::failbit);
	}
	
	~TmpStreamException() { info.exception(original_setting); }
};

#endif
