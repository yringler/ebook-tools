#ifndef RANGE_H
#define RANGE_H

struct Range
{
	int start;
	int finish;
public:
	Range(int a_start=0, int a_finish=0) : 
		start(a_start), finish(a_finish) {}

	int rangeSize() const { return finish - start + 1; }
	bool operator==(const Range & comp) const { 
		return start == comp.start && finish == comp.finish;
	}
};

#endif
