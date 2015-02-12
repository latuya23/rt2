#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "Light.h"

class DirectionalLight: public Light {
public:
	DirectionalLight();
	DirectionalLight(vec3 pos, Color c, vec3 dir);
	virtual ~DirectionalLight();
	virtual vec3 GetAttenuation(){return NULL;}
	virtual bool IsPointLight(){return false;}
	virtual bool IsDirLight(){return true;}
};

#endif /* DIRECTIONALLIGHT_H_ */
