#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
: Light("directional light", vec3(0,0,0),Color(0.0,0.0,0.0),vec3(0,0,0),true)
{
}

DirectionalLight::DirectionalLight(vec3 pos, Color c,vec3 dir)
: Light("directional light", pos, c, dir,true)
{
}

DirectionalLight::~DirectionalLight() {
	// TODO Auto-generated destructor stub
}
