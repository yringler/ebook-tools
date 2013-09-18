#ifndef TMPSTREAMEXCEPTION
#define TMPSTREAMEXCEPTION

#include <ios>

class TmpStreamException
{
private:
	short original_setting;
	basic_ios & info;
public:
	TmpStreamException(basic_ios & a_info) : info(a_info)
	{
		using namespace std::ios_base::iostate;
		original_setting = info.exceptions();
		info.exceptions(badbit | eofbit | failbit);
	}
	
	~TmpStreamException() { info.exception(original_setting); }
}

#endif
