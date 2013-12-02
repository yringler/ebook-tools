#ifndef SHARED_AUTO_PTR_H
#define SHARED_AUTO_PTR_H

#include <cassert>

/*
 * I didn't plan at all for const
 * Don't use const
 *
 * Usage: if assigned with SharedAutoPtr, doesn't take control
 * 	if assigned with raw pointer, assumes ownership
 * 	(which means deleted by destructor)
 */

template<typename T>
class SharedAutoPtr
{
private:
	T * raw_ptr;
	bool own;
public:
	SharedAutoPtr & operator=(SharedAutoPtr & other) {
		if(own) delete raw_ptr;

		raw_ptr = other.get();
		own = false;

		return *this;
	}
	SharedAutoPtr & operator=(T * other) { 
		if(own) delete raw_ptr;

		raw_ptr = other;
		own = true;

		return *this;
	}

	SharedAutoPtr() { raw_ptr = 0, own = 0; }
	SharedAutoPtr(T * other) { operator=(other); }
	SharedAutoPtr(SharedAutoPtr & other) { operator=(other); }

	~SharedAutoPtr() { 
		if(own) {
			assert(raw_ptr);
			delete raw_ptr; 
		}
	}

	T * get() { return raw_ptr; }
	// I might remove own requirement if needed
	T * release() { 
		assert(raw_ptr && own);

		T * tmp = raw_ptr;
		raw_ptr = 0;
		own = false;

		return tmp;
	}
	void aquire(SharedAutoPtr other) { 
		raw_ptr = other.release(); 
		own = true;
	}
};

#endif
