#ifndef CAMERA_H_
#define CAMERA_H_

#include "Sample.h"
#include "Ray.h"
#include <iostream>
#include <glm/glm.hpp>

class Camera{
private:
	int  m_width;
	int  m_height;
	glm::dvec3 m_eye;
	glm::dvec3 m_center;
	glm::dvec3 m_up;
	glm::dvec3 m_w;
	glm::dvec3 m_u;
	glm::dvec3 m_v;
	double m_fovx;
	double m_fov;
	glm::dvec3 m_lookFrom;
	glm::dvec3 m_lookAt;
public:
	Camera();
	Camera(glm::dvec3 lookFrom, glm::dvec3 lookAt, glm::dvec3 up, double fov);
	virtual ~Camera();
	glm::dvec3 GetlookFrom(){return m_lookFrom;}
	glm::dvec3 GetlookAt(){return m_lookAt;}
	glm::dvec3 Getup(){return m_up;}
	double Getfov(){return m_fov;}
	void SetCamera(glm::dvec3 lookFrom, glm::dvec3 lookAt, glm::dvec3 up, double fov);
	void SetAspect(int x, int y);
	void GenerateRay(Sample sample, Ray* ray);
};

#endif /* CAMERA_H_ */
