#include "Ray.h"

const double MINT = .001;
const double MAXT = 1000000;
using namespace std;
Ray::Ray(){
	SetRay(vec3(0,0,0),vec3(0,0,0),vec3(0,0,0));
}

Ray::Ray(vec3 q0, vec3 dir, vec3 p0) {
	SetRay(q0,dir,p0);
}

Ray::Ray(vec3 q0, vec3 dir, vec3 p0, double tmax) {
	SetRay(q0,dir,p0,tmax);
}

Ray::Ray(vec3 q0, vec3 dir, vec3 p0, double tmin, double tmax) {
	SetRay(q0,dir,p0,tmin,tmax);
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

vec3 Ray::evaluate(double t){
	vec3 temp=m_dir;
	scale(temp,t);
	add(temp,m_p0,temp);
	return temp;
}

void Ray::SetRay(vec3 q0, vec3 dir, vec3 p0){
	m_q0 = q0;
	m_dir = dir; //unit vector direction
	m_p0= p0; //real starting point
	m_tmin=MINT;
	m_tmax=MAXT;
}

void Ray::SetRay(vec3 q0, vec3 dir, vec3 p0, double tmax){
	m_q0 = q0;
	m_dir = dir; //unit vector direction
	m_p0= p0; //real starting point
	m_tmin=MINT;
	m_tmax=tmax;
}

void Ray::SetRay(vec3 q0, vec3 dir, vec3 p0, double tmin, double tmax){
	m_q0 = q0;
	m_dir = dir; //unit vector direction
	m_p0= p0; //real starting point
	m_tmin=tmin;
	m_tmax=tmax;
}

void Ray::PrintRay(){
	cout << "q0 =(" << m_q0.x << "," << m_q0.y << "," << m_q0.z << "), dir =(" << m_dir.x << "," << m_dir.y << "," << m_dir.z<< ")"<<endl;
}
