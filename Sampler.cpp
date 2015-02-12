#include <cstdlib>
#include "Sampler.h"

using namespace std;

Sampler::Sampler() {
	SetSamplerSize(0,0);
}

Sampler::Sampler(int sizex, int sizey) {
	m_sizex=sizex;
	m_sizey=sizey;
	m_currx=0;
	m_curry=0;
	cout << "sampler size: " <<sizex<<sizey<<endl;
}

Sampler::~Sampler() {
	// TODO Auto-generated destructor stub
}

void Sampler::SetSamplerSize(int sizex, int sizey){
	m_sizex=sizex;
	m_sizey=sizey;
	m_currx=0;
	m_curry=0;
}

bool Sampler::GetSample(Sample* sample){
	//It will generate (x,y) of a screen sample and return true.
	//Next time it gets called, it will generate another sample
	//for the next pixel. It will return false when all the samples
	//from all the pixels
	//are generated. to do multi-sample
	//per pixel, we need to modify this class.
	if (m_currx==m_sizex){
		return false;
	}
	else {
		Sample s(m_currx,m_curry);
		*sample = s;
		m_curry++;
		if(m_curry==m_sizey){
			m_currx++;
			m_curry=0;
		}
		return true;
	}
	cout << "YOU ARE NOT SUPPOSED TO GET HERE!!!"<<endl;
	exit(1);
	return false;
}
