#ifndef LOCATION_H
#define LOCATION_H

// tells program where he is in the file, like a sign post
// eg "now your at a level 3 labled 'homeward bound'"
// levels start at 0 (book), and go up untill reach actuall content
struct Location
{
	std::wstring lable;
	short level;
};

/*
 * in all these templates:
 * IterT is assumed to be iter to union, as per typedefs.h
 * return 0 on failure
 */

// move until on location
template <typename IterT>
bool moveToLocation(IterT & move, IterT end) {
	for(IterT tmp = move; tmp != end; tmp++)
		if(tmp.active() == 2) {
			move = tmp;
			return true;
		}
	return 0;
}

// move until on location equal to arg
template <typename IterT>
void moveToLocation(IterT & move, IterT end, Location location) {
	IterT tmp = move;
	while(moveToLocation(tmp)) {
		if(*(tmp->second()) == location) {
			move = tmp;
			return true;
		} else {
			tmp++;
		}
	}
	return 0;
}

// highest is understood to be one before content, ie a union.first
template <typename IterT>
bool isAtHighestLocation(IterT & iter) {
	return (iter->active() == 2 && iter[1]->active() == 1);
}

template <typename IterT>
bool moveToHighestLocation(IterT & move, IterT end)
{
	IterT tmp = move;
	while(moveToLocation(tmp)) {
		if(isAtHighestLocation(tmp)) {
			move = tmp;
			return true;
		}
	}
	return 0;
}

// if after move loc is diffrent, moves both forward again
template <typename IterT>
bool moveToHighestLocationTogether(IterT & am, IterT ae, IterT & bm, IterT be) {
	IterT ta=am;
	IterT tb=bm;

	while(true) {
		if(moveToHighestLocation(ta) && moveToHighestLocation(tb)) {
			if(ta->second() == tb->second()) {
				am = ta;
				bm = tb;
				return true;
			}
		} else
			return 0;
	}
}
#endif
