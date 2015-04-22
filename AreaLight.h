#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "Light.h"

class AreaLight: public Light {
 private:
  double m_kc,m_kl,m_kq;//constant, linear, quadratic
  double m_length;
  int m_sqrtSamples;
 public:
  AreaLight();
  AreaLight(glm::dvec3 pos, Color c, glm::dvec3 dir, double length, int samples);
  virtual ~AreaLight();
  virtual bool IsPointLight(){return false;}
  virtual bool IsDirLight(){return false;}
  void SetAttenuation(double kc, double kl, double kq);
  void SetKc(double kc);
  void SetKl(double kl);
  void SetKq(double kq);
  glm::dvec3 GetAttenuation();
  double GetKc(){return m_kc;}
  double GetKl(){return m_kl;}
  double GetKq(){return m_kq;}
  glm::dvec3 GetSamplePos(int i);
};

#endif /* AREALIGHT_H_ */
