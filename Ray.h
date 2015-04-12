#ifndef RAY_H_
#define RAY_H_
#include <iostream>
#include <glm/glm.hpp>

//a ray with initial point r0 and direction r1
class Ray {
public:
	Ray();
	Ray(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0);
	Ray(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmax);
	Ray(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmin, double tmax);
	virtual ~Ray();
	void PrintRay();
	glm::vec3 evaluate(double t);
	void SetRay(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0);
	void SetRay(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmax);
	void SetRay(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmin, double tmax);
	glm::vec3 Getq0(){return  m_q0;}
	glm::vec3 Getp0(){return m_p0;}
	glm::vec3 GetD(){return m_dir;}
	double Gettmin(){return m_tmin;}
	double Gettmax(){return m_tmax;}
private:
	glm::vec3 m_q0;
	glm::vec3 m_dir;
	glm::vec3 m_p0;
	double m_tmin;
	double m_tmax;
};

#endif /* RAY_H_ */
