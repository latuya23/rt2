#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
: Light("directional light", glm::vec3(0,0,0),Color(0.0,0.0,0.0),glm::vec3(0,0,0),true)
{
}

DirectionalLight::DirectionalLight(glm::vec3 pos, Color c,glm::vec3 dir)
: Light("directional light", pos, c, dir,true)
{
}

DirectionalLight::~DirectionalLight() {
	// TODO Auto-generated destructor stub
}
