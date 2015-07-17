#ifndef MARKER_DICTIONARY_H
#define MARKER_DICTIONARY_H

// translates from marker to depth
template <typename CharT>
class MarkerDictionary
{
private:
	typedef std::basic_string<CharT> string;

	String dict;	// translates
	bool marker_set;
	CharT m_title_marker;	// title not a div (see there)
	const String markers;	// valid markers
public:
	// I don't have to make it const, but why not?
	MarkerDictionary(const String & str) : markers(str) {
		marker_set = false;
	}
	bool is_marker(CharT ch) {
		return markers.find(ch) != String::npos;
	}
	bool exists(CharT marker) { 
		assert(marker != m_title_marker);
		return dict.find(marker) != String::npos;
	}
	void title_marker(CharT marker) { 
		assert(not marker_set);
		m_title_marker = marker; 
		marker_set = true;
	}
	void add(CharT marker) {
		if(!exists(marker))
			dict += marker;
	}
	int depth(CharT marker) {
		assert(exists(marker));
		return dict.find(marker);
	}
};

#endif
