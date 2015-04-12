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
	glm::vec3 m_eye;
	glm::vec3 m_center;
	glm::vec3 m_up;
	glm::vec3 m_w;
	glm::vec3 m_u;
	glm::vec3 m_v;
	double m_fovx;
	double m_fov;
	glm::vec3 m_lookFrom;
	glm::vec3 m_lookAt;
public:
	Camera();
	Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 up, double fov);
	virtual ~Camera();
	glm::vec3 GetlookFrom(){return m_lookFrom;}
	glm::vec3 GetlookAt(){return m_lookAt;}
	glm::vec3 Getup(){return m_up;}
	double Getfov(){return m_fov;}
	void SetCamera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 up, double fov);
	void SetAspect(int* x, int* y);
	void GenerateRay(Sample sample, Ray* ray);
};

#endif /* CAMERA_H_ */
