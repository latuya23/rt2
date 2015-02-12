#ifndef COLOR_H_
#define COLOR_H_

#include <stdio.h>
#include <stdlib.h>

class Color {
private:
	double m_r,m_g,m_b;

public:
	Color();
	Color(double r, double g, double b);
	virtual ~Color();
	double GetR(){return m_r;}
	double GetG(){return m_g;}
	double GetB(){return m_b;}
	void SetColor(double r, double g, double b);
	void PrintColor();

	friend Color operator+(const Color &c1, const Color &c2); //Add Color+Color
	Color operator+=(const Color &c1);
	friend Color operator-(const Color &c1, const Color &c2);//Subtract Color-Color
	friend Color operator*(const double &scalar, const Color &c2);//Multiply (float)scalar*Color
	friend Color operator*(const Color &c1, const Color &c2);//multiply color*color
	friend Color operator/(const Color &c1, const double &scalar);//Divide Color/scalar(float)
};

#endif /* COLOR_H_ */
