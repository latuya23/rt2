#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"
#include "Ray.h"
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Light {
 public:
  enum LIGHT_TYPE{
    NONE,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    AREA_LIGHT
  };
  Light(glm::dvec3 pos=glm::dvec3(0), Color c = Color(0.0,0.0,0.0),
	glm::dvec3 dir=glm::dvec3(0));
  virtual ~Light();
  glm::dvec3 GetPos(){return m_position;}
  Color GetColor(){return m_lightColor;}
  glm::dvec3 GetDir(){return m_dir;} //negative normalized direction of light
  void SetLight(glm::dvec3 pos, Color c, glm::dvec3 dir);
  virtual void GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*>* rays,
				 glm::dvec3 surfNormal) = 0;
  virtual glm::dvec3 GetAttenuation() = 0;
  void Print();
  const char* GetLightTypeStr(LIGHT_TYPE lightType);
 protected:
  Color m_lightColor;
  glm::dvec3 m_position;
  glm::dvec3 m_dir;
  LIGHT_TYPE m_lightType;
  int m_samples;
};

#endif /* LIGHT_H_ */
