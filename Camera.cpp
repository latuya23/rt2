#include "Camera.h"

Camera::Camera() {
	SetCamera(glm::dvec3(0,0,0),glm::dvec3(0,0,0),glm::dvec3(0,0,0),0.0);
}

Camera::Camera(glm::dvec3 lookFrom, glm::dvec3 lookAt, glm::dvec3 up, double fov){
	SetCamera(lookFrom, lookAt, up, fov);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::SetAspect(int x, int y){
	m_width = x;
	m_height = y;
}

void Camera::SetCamera(glm::dvec3 lookFrom, glm::dvec3 lookAt, glm::dvec3 up, double fov){
	m_lookFrom=lookFrom;
	m_lookAt=lookAt;
	m_up=up;
	m_fov=fov;   
	m_w = lookFrom - lookAt; // eye-center.
	m_w = glm::normalize(m_w);//w = a/|a|
	m_u = glm::cross(up, m_w); // u=bxw
	m_u = glm::normalize(m_u); /// u = bxw / |bxw|
	m_v = glm::cross(m_w, m_u); //v = wxu
}

void Camera::GenerateRay(Sample sample, Ray* ray){
		//Create a ray starting from the camera that passes through the
        //corresponding pixel (sample.x, sample.y) on the image plane.
        //(from last week discussion, and also section 10.1 in Shirley’s book)]
		double thetaInRadians = ((double)m_fov*.5d)*3.14159265/180.0;
		double beta = 
		  (double)tan(thetaInRadians)*
		  ((m_height*.5) - (double)sample.GetY())/(double)(m_height*.5);
		double alpha = (double)tan(thetaInRadians)*((double)m_width/(double)m_height)*(((double)sample.GetX() - ((double)m_width - 1.0)*.5))/(((double)m_width - 1.0)*.5);
		glm::dvec3 t1 = glm::dvec3(m_u.x*alpha,m_u.y*alpha,m_u.z*alpha); //u*alpha
		glm::dvec3 t2 = glm::dvec3(m_v.x*beta,m_v.y*beta,m_v.z*beta);  //v*beta
		glm::dvec3 t3 = glm::dvec3(0,0,0);
		glm::dvec3 t4 = glm::dvec3(0,0,0);
		t4 = t1 + t2;  //add alpha*u and beta*v components
		t3 = t4-m_w;  // subtract w
		t3 = glm::normalize(t3);// t3 = (alpha*u + beta*v - w)/ |(alpha*u + beta*v - w)|    a.k.a direction normalized
		*ray = Ray(m_lookFrom, t3, m_lookFrom); //ray = eye + (alpha*u + beta*v - w)/ |(alpha*u + beta*v - w)|
}
