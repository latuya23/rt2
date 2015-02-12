#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "Sample.h"

class Sampler {
private:
	int m_sizex;
	int m_sizey;
	int m_currx;
	int m_curry;

public:
	Sampler();
	Sampler(int sizex, int sizey);
	virtual ~Sampler();
	void SetSamplerSize(int sizex, int sizey);
	bool GetSample(Sample* sample);
	int GetSizeX(){return m_sizex;}
	int GetSizeY(){return m_sizey;}
};

#endif /* SAMPLER_H_ */
