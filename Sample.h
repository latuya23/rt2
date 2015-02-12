#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <iostream>

class Sample {
private:
	int m_x;
	int m_y;

public:
	Sample(int x, int y);
	virtual ~Sample();
	int GetX(){return m_x;}
	int GetY(){return m_y;}
	void SetSample(int x, int y);
	void PrintSample();
};

#endif /* SAMPLE_H_ */
