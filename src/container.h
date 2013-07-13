#ifndef SEFER_CONTAINER_H
#define SEFER_CONTAINER_H

#include <deque>
#include <string>
#include "component.h"

namespace sefer {

// A container contains content
// Content could be a container
template <typename T>	// What contains
class Container : public Component, private std::deque<T>
{
	protected:
		T & last() { return std::deque<T>::front(); }
	public:
		Container(int i = 0, std::wstring str = "") 
			: Component(i,str) {}

		void add(const std::string & str = "") { 
			push_front( T(str,std::deque<T>::size()+1) ); 
		}
		void next() { std::deque<T>::pop_back(); }
		bool finished() { return std::deque<T>::empty(); }

		T & content() { return std::deque<T>::back(); }
};

}	// end namespace sefer

#endif
