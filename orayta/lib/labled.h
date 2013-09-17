#ifndef LABLED_H
#define LABLED_H

#include <string>

template<class T>
struct Labled : T
{
	std::string lable;
}
