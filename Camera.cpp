#include "Camera.h"

Camera::Camera() {
	SetCamera(vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),0.0);

}

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, double fov){
	SetCamera(lookFrom, lookAt, up, fov);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::SetAspect(int* x, int* y){
	m_width = *x;
	m_height = *y;
}

void Camera::SetCamera(vec3 lookFrom, vec3 lookAt, vec3 up, double fov){
	m_lookFrom=lookFrom;
	m_lookAt=lookAt;
	m_up=up;
	m_fov=fov;
	sub(m_w,  lookFrom, lookAt); // eye-center.
	normalize(m_w);//w = a/|a|
	vec3 temp = vec3(0,0,0);
	m_u = cross(temp, up, m_w); // u=bxw
	normalize(m_u); /// u = bxw / |bxw|
	m_v = cross(temp, m_w, m_u); //v = wxu
}

void Camera::GenerateRay(Sample sample, Ray* ray){
		//Create a ray starting from the camera that passes through the
        //corresponding pixel (sample.x, sample.y) on the image plane.
        //(from last week discussion, and also section 10.1 in Shirley’s book)]
		float thetaInRadians = ((float)m_fov/2.0)*3.14159265/180.0;
		float beta = 
		  (float)tan(thetaInRadians)*
		  ((m_height/2.0) - (float)sample.GetY())/(float)(m_height/2.0);
		float alpha = (float)tan(thetaInRadians)*((float)m_width/(float)m_height)*(((float)sample.GetX() - ((float)m_width - 1.0)/2.0))/(((float)m_width - 1.0)/2.0);
		vec3 t1 = vec3(m_u.x*alpha,m_u.y*alpha,m_u.z*alpha); //u*alpha
		vec3 t2 = vec3(m_v.x*beta,m_v.y*beta,m_v.z*beta);  //v*beta
		vec3 t3 = vec3(0,0,0);
		vec3 t4 = vec3(0,0,0);
		add(t4, t1, t2);  //add alpha*u and beta*v components
		sub(t3,t4,m_w);  // subtract w
		normalize(t3);// t3 = (alpha*u + beta*v - w)/ |(alpha*u + beta*v - w)|    a.k.a direction normalized
		*ray = Ray(m_lookFrom, t3, m_lookFrom); //ray = eye + (alpha*u + beta*v - w)/ |(alpha*u + beta*v - w)|
}
