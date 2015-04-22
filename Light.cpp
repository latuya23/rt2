#include "Light.h"
#include "AreaLight.h"

Light::Light() {
  m_Light="undefined light";
}

Light::Light(std::string light, glm::dvec3 pos, Color c, glm::dvec3 dir, bool midirl){
  SetLight(pos,c,dir,midirl);
  m_Light=light;
  m_lightType = NONE;
}

Light::~Light() {
  // TODO Auto-generated destructor stub
}

void Light::SetLight(glm::dvec3 pos, Color c, glm::dvec3 dir, bool midirl){
  m_position=pos;
  m_lightColor=c;
  m_dir= dir * -1.0; //reverse normalized dir of light
  m_idirl=midirl;
}

void Light::GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*> *rays, glm::dvec3 surfNormal){
  Ray* lRay;
  if(m_lightType == DIRECTIONAL_LIGHT){
    glm::dvec3 temp2;
    temp2 = (surfNormal*.01) + inPoint; // add something in the direction of the light
    lRay = new Ray(temp2, m_dir, inPoint); //generate ray from inPoint towards reverse light direction
    rays->push_back(lRay);
  }
  else if (m_lightType == POINT_LIGHT) {
    glm::dvec3 inP2LightV = m_position - inPoint;//vector to light
    double dist = glm::length(inP2LightV);//tmax for ray
    glm::dvec3 step2Light = (surfNormal*.01) + inPoint; //add something in the direction of the light then shoot the ray
    lRay = new Ray(step2Light,glm::normalize(inP2LightV), inPoint,dist); //generate ray from temp3 towards the light with // TODO: max dist
    rays->push_back(lRay);
  }
  else if (m_lightType == AREA_LIGHT){
    for (int i = 0; i < m_samples; i++){
      glm::dvec3 inP2LightV =
	(*(AreaLight*)this).GetSamplePos(i) - inPoint;//vector to light
      double dist = glm::length(inP2LightV);//tmax for ray
      glm::dvec3 step2Light = (surfNormal*.01) + inPoint; //add something in the direction of the light then shoot the ray
      lRay = new Ray(step2Light,glm::normalize(inP2LightV), inPoint,dist); //generate ray from temp3 towards the light with // TODO: max dist
      rays->push_back(lRay);
    }
  }
}

bool Light::IsPointLight(){
  std::cout<<"error undefined light"<<std::endl;
  return false;
}
bool Light::IsDirLight(){
  std::cout<<"error undefined light"<<std::endl;
  return false;
}

void Light::Print(){
  std::cout<<"color:"<<std::endl;
  m_lightColor.PrintColor();
  std::cout<<"position:"<<std::endl;
  std::cout<<"x: "<<m_position.x<<" y: "<<m_position.y<<" z: "<<m_position.z<<std::endl;
  std::cout<<"is directional light: "<<IsDirLight()<<std::endl;
  std::cout<<"is point light: "<<IsPointLight()<<std::endl;
}
