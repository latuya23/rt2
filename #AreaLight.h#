#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "Light.h"

class AreaLight: public Light {
 private:
  double m_kc,m_kl,m_kq;//constant, linear, quadratic
  double m_length;
  int m_sqrtSamples;
  double m_delta;
 public:
  AreaLight(glm::dvec3 pos=glm::dvec3(0), Color c = Color(0.0,0.0,0.0),
	    glm::dvec3 dir=glm::dvec3(0), double length = 2.0,
	    int samples=9);
  virtual ~AreaLight();
  virtual void GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*>* rays,
				 glm::dvec3 surfNormal);
  void SetAttenuation(double kc, double kl, double kq);
  void SetKc(double kc);
  void SetKl(double kl);
  void SetKq(double kq);
  virtual glm::dvec3 GetAttenuation();
  double GetKc(){return m_kc;}
  double GetKl(){return m_kl;}
  double GetKq(){return m_kq;}
  glm::dvec3 GetSamplePos(int i, bool jitter = true);
};

#endif /* AREALIGHT_H_ */
