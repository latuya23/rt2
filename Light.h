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
  bool m_idirl;
  Light();
  Light(std::string light, glm::dvec3 pos, Color c, glm::dvec3 dir, bool midirl);
  virtual ~Light();
  std::string GetName(){return m_Light;}
  glm::dvec3 GetPos(){return m_position;}
  Color GetColor(){return m_lightColor;}
  glm::dvec3 GetDir(){return m_dir;} //negative normalized direction of light
  bool GetMIDir(){return m_idirl;}
  void SetLight(glm::dvec3 pos, Color c, glm::dvec3 dir, bool midirl);
  void GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*>* rays,
			glm::dvec3 surfNormal);
  virtual glm::dvec3 GetAttenuation() = 0;
  void Print();
  virtual bool IsPointLight();
  virtual bool IsDirLight();
  //virtual glm::dvec3 GetSamplePos() = 0;
 protected:
  std::string m_Light;
  Color m_lightColor;
  glm::dvec3 m_position;
  glm::dvec3 m_dir;
  LIGHT_TYPE m_lightType;
  int m_samples;
};

#endif /* LIGHT_H_ */
