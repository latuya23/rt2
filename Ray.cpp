#include "Ray.h"

const double MINT = .001;
const double MAXT = 1000000;

Ray::Ray(){
	SetRay(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0,0,0));
}

Ray::Ray(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0) {
	SetRay(q0,dir,p0);
}

Ray::Ray(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmax) {
	SetRay(q0,dir,p0,tmax);
}

Ray::Ray(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmin, double tmax) {
	SetRay(q0,dir,p0,tmin,tmax);
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

glm::vec3 Ray::evaluate(double t){
	glm::vec3 temp=m_dir;
	temp = temp*(float)t;
	temp = m_p0 + temp;
	return temp;
}

void Ray::SetRay(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0){
	m_q0 = q0;
	m_dir = dir; //unit vector direction
	m_p0= p0; //real starting point
	m_tmin=MINT;
	m_tmax=MAXT;
}

void Ray::SetRay(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmax){
	m_q0 = q0;
	m_dir = dir; //unit vector direction
	m_p0= p0; //real starting point
	m_tmin=MINT;
	m_tmax=tmax;
}

void Ray::SetRay(glm::vec3 q0, glm::vec3 dir, glm::vec3 p0, double tmin, double tmax){
	m_q0 = q0;
	m_dir = dir; //unit vector direction
	m_p0= p0; //real starting point
	m_tmin=tmin;
	m_tmax=tmax;
}

void Ray::PrintRay(){
  std::cout << "q0 =(" << m_q0.x << "," << m_q0.y << "," << m_q0.z << "), dir =(" << m_dir.x << "," << m_dir.y << "," << m_dir.z<< ")"<<std::endl;
}
