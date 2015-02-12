#ifndef RAY_H_
#define RAY_H_
#include "nv/nv_math.h"
#include <iostream>

using namespace std;
//a ray with initial point r0 and direction r1
class Ray {
public:
	Ray();
	Ray(vec3 q0, vec3 dir, vec3 p0);
	Ray(vec3 q0, vec3 dir, vec3 p0, double tmax);
	Ray(vec3 q0, vec3 dir, vec3 p0, double tmin, double tmax);
	virtual ~Ray();
	void PrintRay();
	vec3 evaluate(double t);
	void SetRay(vec3 q0, vec3 dir, vec3 p0);
	void SetRay(vec3 q0, vec3 dir, vec3 p0, double tmax);
	void SetRay(vec3 q0, vec3 dir, vec3 p0, double tmin, double tmax);
	vec3 Getq0(){return  m_q0;}
	vec3 Getp0(){return m_p0;}
	vec3 GetD(){return m_dir;}
	double Gettmin(){return m_tmin;}
	double Gettmax(){return m_tmax;}
private:
	vec3 m_q0;
	vec3 m_dir;
	vec3 m_p0;
	double m_tmin;
	double m_tmax;
};

#endif /* RAY_H_ */
