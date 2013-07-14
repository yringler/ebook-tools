#ifndef SEFER_CONTAINER_H
#define SEFER_CONTAINER_H

#include <deque>
#include <string>
#include "component.h"

namespace sefer {

// A container contains content
// Content could be a container
template <typename T>	// What contains
class Container : public Component
{
	private :
		std::deque<T> m_content;
	protected:
		T & last() { return m_content.front(); }
	public:
		Container(int i = 0, std::wstring str = "") 
			: Component(i,str) {}

		void add(const std::string & str = "") { 
			push_front( T(str,m_content.size()+1) ); 
		}
		void next() { m_content.pop_back(); }
		bool finished() { return m_content.empty(); }

		T & content() { return m_content.back(); }
};

}	// end namespace sefer

#endif
