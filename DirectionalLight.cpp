#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::dvec3 pos, Color c,glm::dvec3 dir)
: Light(pos, c, dir)
{
   m_lightType = Light::DIRECTIONAL_LIGHT;
   m_samples = 1;
}

DirectionalLight::~DirectionalLight() {
	// TODO Auto-generated destructor stub
}

void DirectionalLight::GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*> *rays,
					 glm::dvec3 surfNormal){
  Ray* lRay;
  glm::dvec3 temp2;
  temp2 = (surfNormal*.01) + inPoint; // add something in the direction of the light
  lRay = new Ray(temp2, m_dir, inPoint); //generate ray from inPoint towards reverse light direction
  rays->push_back(lRay);
}
