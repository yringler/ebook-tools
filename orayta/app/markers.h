#include <string>
const string MARKERS("$@~!^");
bool is_marker(char c) { return MARKERS.find(c) != MARKERS.end(); }
