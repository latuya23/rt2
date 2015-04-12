#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "Light.h"

class DirectionalLight: public Light {
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 pos, Color c, glm::vec3 dir);
	virtual ~DirectionalLight();
	virtual glm::vec3 GetAttenuation(){return glm::vec3(0);}
	virtual bool IsPointLight(){return false;}
	virtual bool IsDirLight(){return true;}
};

#endif /* DIRECTIONALLIGHT_H_ */
