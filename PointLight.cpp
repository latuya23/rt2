#include "PointLight.h"

PointLight::PointLight()
	: Light("point light", glm::vec3(0,0,0) ,Color(0.0,0.0,0.0), glm::vec3(0,0,0),false)
{
	SetAttenuation(1.0, 0.0, 0.0);//sets default attenuation to 1,0,0
}

PointLight::PointLight(glm::vec3 pos, Color c, glm::vec3 dir)
	: Light("point light", pos, c, dir,false)
{
	SetAttenuation(1.0,0.0,0.0);//sets default attenuation to 1,0,0
}

PointLight::PointLight(glm::vec3 pos, Color c, glm::vec3 dir, double kc, double kl, double kq)
	: Light("Point light", pos, c, dir, false)
{
	SetAttenuation(kc,kl,kq);
}

PointLight::~PointLight() {
	// TODO Auto-generated destructor stub
}

void PointLight::SetAttenuation(double kc, double kl, double kq){
	SetKc(kc);//constant
	SetKl(kl);//linear
	SetKq(kq);//quadratic
}

void PointLight::SetKc(double kc){
	m_kc=kc;//set constant coefficient
}

void PointLight::SetKl(double kl){
	m_kl=kl;//set linear coefficient
}

void PointLight::SetKq(double kq){
	m_kq=kq;//set quadratic coefficient
}

glm::vec3 PointLight::GetAttenuation(){
	//if u call this method you'll get the
	//constant, linear, & quadratic coefficients
	//in a glm::vec3 struct
	return glm::vec3(m_kc,m_kl,m_kq);
}
