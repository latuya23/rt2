#include "BRDF.h"

BRDF::BRDF() {
	//set up a BRDF with all the values set to default
	//ka ambient defaults to .2,.2,.2
	//kd diffuse defaults to .8,.8,.8
	//ks specular defaults to 0,0,0
	//ke emission defaults to 0,0,0
	//kr reflection????? 0,0,0
	//s shininess default to 0.0
	//kt refraction
	Color temp(0.0,0.0,0.0);
	SetBRDF(Color(0.8,0.8,0.8),temp,Color(0.2,0.2,0.2),temp,temp, 0.0,0.0);
}

BRDF::BRDF(Color kd, Color ks, Color ka, Color ke,Color kr, double s, double kt){
	SetBRDF(kd,ks,ka,ke,kr,s,kt);
}

BRDF::~BRDF() {
	// TODO Auto-generated destructor stub
}

void BRDF::SetKd(Color kd){
	// set diffuse component
	m_kd=kd;
}

void BRDF::SetKs(Color ks){
    // set specular component
	m_ks=ks;
}

void BRDF::SetKa(Color ka){
	// set ambient
	m_ka=ka;
}

void BRDF::SetKe(Color ke){
	// ke emission for the surface
	m_ke=ke;
}

void BRDF::SetKr(Color kr){
	// set kr. set the mirror reflection coefficient aka shininess
	m_kr=kr;
}

void BRDF::SetS(double s){
	//set shininess
	// a number in the range [0.0, 128.0]
	m_s=s;
	if (s<0.0){
		m_s=0.0;
	}
	else if(s>128.0){
		m_s=128.0;
	}
}

void BRDF::SetKt(double kt){
	//set refraction index
	m_kt=kt;
}

void BRDF::SetBRDF(Color kd, Color ks, Color ka, Color ke, Color kr, double s, double kt){
	SetKd(kd); //diffuse
	SetKs(ks); //specular
	SetKa(ka); //ambient
	SetKe(ke); //emission
	SetKr(kr); //reflection coefficient
	SetS(s);   //shininess
	SetKt(kt); //refraction
}

void BRDF::PrintBRDF(){
	cout<<"diffuse kd:"<<endl;
	m_kd.PrintColor();
	cout<<"specular ks:"<<endl;
	m_ks.PrintColor();
	cout<<"ambient ka:"<<endl;
	m_ka.PrintColor();
	cout<<"emission ke:"<<endl;
	m_ke.PrintColor();
	cout<<"reflection kr:"<<endl;
	m_kr.PrintColor();
	cout<<"Shininess: "<<m_s<<endl;
	cout<<"Refraction Index:"<<m_kt<<endl;
}



