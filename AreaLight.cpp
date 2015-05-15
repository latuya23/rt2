#include "AreaLight.h"
#include <time.h>

AreaLight::AreaLight(glm::dvec3 pos/*=glm::dvec3(0)*/, Color c/*=Color(0.0,0.0,0.0)*/,
		     glm::dvec3 dir/*=glm::dvec3(0)*/,
		     double length/*=2.0*/, int samples/*=9*/)
: Light(pos, c, dir)
{
   m_lightType = Light::AREA_LIGHT;
   m_length = length;
   m_samples = samples;
   std::cout << "# of samples: " << m_samples << std::endl;
   m_sqrtSamples = sqrt(m_samples);
   std::cout << "sqrt  samples: " << m_sqrtSamples << std::endl;
   m_delta = m_length/(double)m_sqrtSamples;
   std::cout << "delta: " << m_delta << std::endl;
   srand(time(NULL));
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

glm::dvec3 AreaLight::GetSamplePos(int i, bool jitter/*=true*/){
  assert(i < m_samples);
  double randomx = 0.0;
  double randomz = 0.0;
  //jitter = false;
  if (jitter){
    randomx += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/m_delta));
    randomz += static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/m_delta));
  }
  double x = (i % m_sqrtSamples) * m_delta + randomx;
  // std::cout << "x: " << x << std::endl;
  double z = (i / m_sqrtSamples) * m_delta + randomz;
  // std::cout << "z: " << z << std::endl;
  glm::dvec3 pointInLight(m_position.x + x, m_position.y,m_position.z+z);
  return pointInLight;
}

void AreaLight::GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*> *rays, glm::dvec3 surfNormal){
  Ray *lRay;
  for (int i = 0; i < m_samples; i++){
    glm::dvec3 inP2LightV =
      (*(AreaLight*)this).GetSamplePos(i) - inPoint;//vector to light
    double dist = glm::length(inP2LightV);//tmax for ray
    glm::dvec3 step2Light = (surfNormal*.01) + inPoint; //add something in the direction of // TODO: he light then shoot the ray
    lRay = new Ray(step2Light,glm::normalize(inP2LightV), inPoint,dist); //generate ray from temp3 towards the light with max dist
    rays->push_back(lRay);
  }
}









