#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "Light.h"

class PointLight: public Light {
private:
	double m_kc,m_kl,m_kq;//constant, linear, quadratic
public:
	PointLight();
	PointLight(vec3 pos, Color c, vec3 dir);
	PointLight(vec3 pos, Color c, vec3 dir,double kc, double kl, double kq);
	virtual ~PointLight();
	virtual bool IsPointLight(){return true;}
	virtual bool IsDirLight(){return false;}
	void SetAttenuation(double kc, double kl, double kq);
	void SetKc(double kc);
	void SetKl(double kl);
	void SetKq(double kq);
	vec3 GetAttenuation();
	double GetKc(){return m_kc;}
	double GetKl(){return m_kl;}
	double GetKq(){return m_kq;}
};

#endif /* POINTLIGHT_H_ */
