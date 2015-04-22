#include "AreaLight.h"

AreaLight::AreaLight()
: Light("directional light", glm::dvec3(0,0,0),Color(0.0,0.0,0.0),
	glm::dvec3(0,0,0),true)
{
  m_lightType = Light::AREA_LIGHT;
  m_length = 2.0;
  m_samples = 9;
  m_sqrtSamples = 3;
}

AreaLight::AreaLight(glm::dvec3 pos, Color c,glm::dvec3 dir,
		     double length, int samples)
: Light("directional light", pos, c, dir,true)
{
   m_lightType = Light::AREA_LIGHT;
   m_length = length;
   m_samples = samples;
   std::cout << "# of samples: " << m_samples << std::endl;
   m_sqrtSamples = sqrt(m_samples);
   std::cout << "sqrt  samples: " << m_sqrtSamples << std::endl;
}

AreaLight::~AreaLight() {
	// TODO Auto-generated destructor stub
}
void AreaLight::SetAttenuation(double kc, double kl, double kq){
	SetKc(kc);//constant
	SetKl(kl);//linear
	SetKq(kq);//quadratic
}

void AreaLight::SetKc(double kc){
	m_kc=kc;//set constant coefficient
}

void AreaLight::SetKl(double kl){
	m_kl=kl;//set linear coefficient
}

void AreaLight::SetKq(double kq){
	m_kq=kq;//set quadratic coefficient
}

glm::dvec3 AreaLight::GetAttenuation(){
	//if u call this method you'll get the
	//constant, linear, & quadratic coefficients
	//in a glm::dvec3 struct
	return glm::dvec3(m_kc,m_kl,m_kq);
}

glm::dvec3 AreaLight::GetSamplePos(int i){
  assert(i < m_samples);
  int x = i % m_sqrtSamples * m_length;
  int z = i / m_sqrtSamples * m_length;
  glm::dvec3 pointInLight(m_position.x + x, m_position.y,m_position.z+z);
  return pointInLight;
}

//glm::dvec3 









