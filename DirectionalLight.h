#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "Light.h"

class DirectionalLight: public Light {
public:
	DirectionalLight();
	DirectionalLight(glm::dvec3 pos, Color c, glm::dvec3 dir);
	virtual ~DirectionalLight();
	virtual glm::dvec3 GetAttenuation(){return glm::dvec3(0);}
	virtual bool IsPointLight(){return false;}
	virtual bool IsDirLight(){return true;}
};

#endif /* DIRECTIONALLIGHT_H_ */
