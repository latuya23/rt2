#include "Sample.h"
#include <iostream>

Sample::Sample(int x, int y) {
	SetSample(x,y);
}

Sample::~Sample() {
	// TODO Auto-generated destructor stub
}

void Sample::SetSample(int x, int y){
	m_x=x;
	m_y=y;
}

void Sample::PrintSample(){
  std::cout << "x:" << m_x << ", y:" << m_y << std::endl;
}
