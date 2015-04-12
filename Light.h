#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"
#include "Ray.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

class Light {
 protected:
  std::string m_Light;
  Color m_lightColor;
  glm::vec3 m_position;
  glm::vec3 m_dir;
 public:
  bool m_idirl;
  Light();
  Light(std::string light, glm::vec3 pos, Color c, glm::vec3 dir, bool midirl);
  virtual ~Light();
  std::string GetName(){return m_Light;}
  glm::vec3 GetPos(){return m_position;}
  Color GetColor(){return m_lightColor;}
  glm::vec3 GetDir(){return m_dir;} //negative normalized direction of light
  bool GetMIDir(){return m_idirl;}
  void SetLight(glm::vec3 pos, Color c, glm::vec3 dir, bool midirl);
  void GenerateLightRay(glm::vec3 inPoint, Ray* lRay, glm::vec3 surfNormal);
  virtual glm::vec3 GetAttenuation() = 0;
  void Print();
  virtual bool IsPointLight();
  virtual bool IsDirLight();
};

#endif /* LIGHT_H_ */
