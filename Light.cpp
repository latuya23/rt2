#include "Light.h"
#include "AreaLight.h"

Light::Light(glm::dvec3 pos/*=glm::dvec3(0)*/, Color c/*=Color(0.0,0.0,0.0)*/,
	     glm::dvec3 dir/*=glm::dvec3(0)*/){
  SetLight(pos,c,dir);
  m_lightType = NONE;
}

Light::~Light() {
  // TODO Auto-generated destructor stub
}

void Light::SetLight(glm::dvec3 pos, Color c, glm::dvec3 dir){
  m_position=pos;
  m_lightColor=c;
  m_dir= dir * -1.0; //reverse normalized dir of light
  m_lightType = NONE;
}

void Light::Print(){
  std::cout<<"color:"<<std::endl;
  m_lightColor.PrintColor();
  std::cout<<"position:"<<std::endl;
  std::cout<<"x: "<<m_position.x<<" y: "<<m_position.y<<" z: "<<m_position.z<<std::endl;
  std::cout<<"Light Type is: "<< GetLightTypeStr(m_lightType) << std::endl;
}

const char* Light::GetLightTypeStr(LIGHT_TYPE lightType){
  switch (lightType){
  case NONE:   return "No Type"; break;
  case POINT_LIGHT:   return "Point Light"; break;
  case DIRECTIONAL_LIGHT:   return "Directional Light"; break;
  case AREA_LIGHT:   return "Area Light"; break;
  default:        return "None"; break;
  }
}
