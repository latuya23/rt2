#ifndef LIGHT_H_
#define LIGHT_H_

#include "nv/nv_math.h"
#include "Color.h"
#include "Ray.h"
#include <string>
#include <iostream>

using namespace std;

class Light {
private:
	string m_Light;
	Color m_lightColor;
	vec3 m_position;
	vec3 m_dir;
public:
	bool m_idirl;
	Light();
	Light(string light, vec3 pos, Color c, vec3 dir, bool midirl);
	virtual ~Light();
	string GetName(){return m_Light;}
	vec3 GetPos(){return m_position;}
	Color GetColor(){return m_lightColor;}
	vec3 GetDir(){return m_dir;} //negative normalized direction of light
	bool GetMIDir(){return m_idirl;}
	void SetLight(vec3 pos, Color c, vec3 dir, bool midirl);
	void GenerateLightRay(vec3 inPoint, Ray* lRay, vec3 surfNormal);
	virtual vec3 GetAttenuation() = 0;
	void Print();
	virtual bool IsPointLight();
	virtual bool IsDirLight();
};

#endif /* LIGHT_H_ */
