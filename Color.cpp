#include "Color.h"

Color::Color(){
	SetColor(0.0,1.0,0.0);
}
Color::Color(double r, double g, double b) {
	SetColor(r,g,b);
}


Color::~Color() {
	// TODO Auto-generated destructor stub
}

void Color::PrintColor(){
	printf("r:%f, g:%f, b:%f\n",m_r,m_g,m_b);
}

void Color::SetColor(double r, double g, double b){
	m_r=r;
	m_g=g;
	m_b=b;
	if (r>1.0){
		m_r=1.0;
	}
	if (r<0.0){
		m_r=0.0;
	}
	if (g>1.0){
		m_g=1.0;
	}
	if (g<0.0){
		m_g=0.0;
	}
	if (b>1.0){
		m_b=1.0;
	}
	if (b<0.0){
		m_b=0.0;
	}
}

Color operator+(const Color &c1, const Color &c2){
	return Color(c1.m_r+c2.m_r,c1.m_g+c2.m_g,c1.m_b+c2.m_b);
}

Color Color::operator+=(const Color &c1){
		SetColor(m_r+c1.m_r,m_g+c1.m_g,m_b+c1.m_b);
		return *this;
	}

Color operator-(const Color &c1, const Color &c2){
	return Color(c1.m_r-c2.m_r,c1.m_g-c2.m_g,c1.m_b-c2.m_b);
}

Color operator*(const double &scalar, const Color &c1){
	return Color(scalar*c1.m_r,scalar*c1.m_g,scalar*c1.m_b);
}

Color operator*(const Color &c1, const Color &c2){
	return Color(c1.m_r*c2.m_r,c1.m_g*c2.m_g,c1.m_b*c2.m_b);
}

Color operator/(const Color &c1, const double &scalar){
	if (scalar<=0){
		printf("trying to divide color by 0 or neg #");
		exit(1);
	}
	else{
		return Color(c1.m_r/scalar,c1.m_g/scalar,c1.m_b/scalar);
	}
}
