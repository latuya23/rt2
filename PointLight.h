#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "Light.h"

class PointLight: public Light {
private:
	double m_kc,m_kl,m_kq;//constant, linear, quadratic
public:
	PointLight();
	PointLight(glm::dvec3 pos, Color c, glm::dvec3 dir);
	PointLight(glm::dvec3 pos, Color c, glm::dvec3 dir,double kc, double kl, double kq);
	virtual ~PointLight();
	virtual void GenerateLightRays(glm::dvec3 inPoint,
					     std::vector<Ray*>* rays,
					     glm::dvec3 surfNormal);
	void SetAttenuation(double kc, double kl, double kq);
	void SetKc(double kc);
	void SetKl(double kl);
	void SetKq(double kq);
	virtual glm::dvec3 GetAttenuation();
	double GetKc(){return m_kc;}
	double GetKl(){return m_kl;}
	double GetKq(){return m_kq;}
};

#endif /* POINTLIGHT_H_ */
