#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "Light.h"

class DirectionalLight: public Light {
public:
  DirectionalLight(glm::dvec3 pos=glm::dvec3(0),
		   Color c=Color(0.0,0.0,0.0),
		   glm::dvec3 dir=glm::dvec3(0));
	virtual ~DirectionalLight();
	virtual void GenerateLightRays(glm::dvec3 inPoint, std::vector<Ray*>* rays,
				       glm::dvec3 surfNormal);
	virtual glm::dvec3 GetAttenuation(){return glm::dvec3(0);}
	virtual bool IsPointLight(){return false;}
	virtual bool IsDirLight(){return true;}
};

#endif /* DIRECTIONALLIGHT_H_ */
