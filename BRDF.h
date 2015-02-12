#ifndef BRDF_H_
#define BRDF_H_

#include "Color.h"
#include <iostream>

using namespace std;

class BRDF {
private:
	// kd, diffuse component
    // ks specular
	// ka ambient
	// kr is the mirror reflection coefficient
	// ke emission for the surface
	// s shininess
	// kt refraction
		Color m_kd,m_ks,m_ka,m_ke,m_kr;
		double m_s,m_kt;
public:
	BRDF();
	BRDF(Color kd, Color ks, Color ka, Color ke, Color kr, double s, double kt);
	virtual ~BRDF();
	Color GetKd(){return m_kd;}
	Color GetKs(){return m_ks;}
	Color GetKa(){return m_ka;}
	Color GetKe(){return m_ke;}
	Color GetKr(){return m_kr;}
	double GetS(){return m_s;}
	double GetKt(){return m_kt;}
	void SetKd(Color kd);
	void SetKs(Color ks);
	void SetKa(Color ka);
	void SetKe(Color ke);
	void SetKr(Color kr);
	void SetS(double s);
	void SetKt(double kt);
	void SetBRDF(Color kd, Color ks, Color ka, Color ke, Color kr, double s, double kt);
	void PrintBRDF();
};

#endif /* BRDF_H_ */
