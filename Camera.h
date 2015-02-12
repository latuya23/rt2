#ifndef CAMERA_H_
#define CAMERA_H_

#include "Sample.h"
#include "Ray.h"
#include <iostream>

using namespace std;

class Camera{
private:
	int  m_width;
	int  m_height;
	vec3 m_eye;
	vec3 m_center;
	vec3 m_up;
	vec3 m_w;
	vec3 m_u;
	vec3 m_v;
	double m_fovx;
	double m_fov;
	vec3 m_lookFrom;
	vec3 m_lookAt;
public:
	Camera();
	Camera(vec3 lookFrom, vec3 lookAt, vec3 up, double fov);
	virtual ~Camera();
	vec3 GetlookFrom(){return m_lookFrom;}
	vec3 GetlookAt(){return m_lookAt;}
	vec3 Getup(){return m_up;}
	double Getfov(){return m_fov;}
	void SetCamera(vec3 lookFrom, vec3 lookAt, vec3 up, double fov);
	void SetAspect(int* x, int* y);
	void GenerateRay(Sample sample, Ray* ray);
};

#endif /* CAMERA_H_ */
