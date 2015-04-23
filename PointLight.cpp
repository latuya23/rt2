#include "PointLight.h"

PointLight::PointLight(glm::dvec3 pos, Color c, glm::dvec3 dir)
	: Light(pos, c, dir)
{
	SetAttenuation(1.0,0.0,0.0);//sets default attenuation to 1,0,0
	m_lightType = Light::POINT_LIGHT;
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

glm::dvec3 PointLight::GetAttenuation(){
	//if u call this method you'll get the
	//constant, linear, & quadratic coefficients
	//in a glm::dvec3 struct
	return glm::dvec3(m_kc,m_kl,m_kq);
}

void PointLight::GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*>* rays,
					 glm::dvec3 surfNormal){
  Ray* lRay;
  glm::dvec3 inP2LightV = m_position - inPoint;//vector to light
  double dist = glm::length(inP2LightV);//tmax for ray
  glm::dvec3 step2Light = (surfNormal*.01) + inPoint; //add something in the direction of the light then shoot the ray
  lRay = new Ray(step2Light,glm::normalize(inP2LightV), inPoint,dist); //generate ray from towards the light with  max dist
  rays->push_back(lRay);
}
