#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
: Light("directional light", glm::dvec3(0,0,0),Color(0.0,0.0,0.0),glm::dvec3(0,0,0),true)
{
}

DirectionalLight::DirectionalLight(glm::dvec3 pos, Color c,glm::dvec3 dir)
: Light("directional light", pos, c, dir,true)
{
}

DirectionalLight::~DirectionalLight() {
	// TODO Auto-generated destructor stub
}
