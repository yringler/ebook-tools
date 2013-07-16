#ifndef RANGE_H
#define RANGE_H

class Range
{
private:
	int m_start;
	int m_finish;
public:
	Range(int a_start=0, int a_finish=0) : 
		m_start(a_start), m_finish(a_finish) {}

	void start(int a_start) { m_start = a_start; }
	int start() const { return m_start; }
	void finish(int a_finish) { m_finish = a_finish; }
	int finish() const { return m_finish; }
	void set(int a_start, int a_finish) { 
		start(a_start);
		finish(a_finish);
	}

	int rangeSize() const { return finish() - start() + 1; }
	bool operator==(const Range & comp) const { 
		return start() == comp.start() && finish() == comp.finish();
	}
};

#endif
