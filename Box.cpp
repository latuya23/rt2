/*
 * Carlos Macias
 * carlos.macias23@gmail.com
 * Box is a class that represents a box object
 * inherits from Primitive 
 * it has 2 vectors min and max
 * it has the intersectionAABB with ray method 
 * uses the ray-AABB intersection test from 3d game engine design 
 */
#include "Box.h"

int Box::next_id=0;
/*
Box::Box(glm::dvec3 minv, glm::dvec3 maxv) {
  m_min = minv;
  m_max = maxv;
  m_transform = glm::dmat4(1.0);
  m_boxId = Box::next_box_id();
  SetVertices();
  }*/

Box::Box(glm::dvec3 minv, glm::dvec3 maxv, glm::dmat4 modelM) {
  m_min = minv;
  m_max = maxv;
  m_transform = modelM;
  m_boxId = Box::next_box_id();
  SetVertices();
}

Box::~Box(){
}

int Box::next_box_id(){
  return next_id++;
}

void Box::Print(){
  std::cout << "box printing: " << std::endl;
  std::cout << "mins: " << glm::to_string(m_min) << std::endl;
  std::cout << "maxs: " << glm::to_string(m_max) << std::endl;
}

void Box::SetVertices(){
  m_ltf = glm::dvec3(m_min.x,m_max.y,m_max.z);
  m_rtf = glm::dvec3(m_max.x,m_max.y,m_max.z);
  m_lbf = glm::dvec3(m_min.x,m_min.y,m_max.z);
  m_rbf = glm::dvec3(m_max.x,m_min.y,m_max.z);
  m_ltn = glm::dvec3(m_min.x,m_max.y,m_min.z);
  m_rtn = glm::dvec3(m_max.x,m_max.y,m_min.z);
  m_lbn = glm::dvec3(m_min.x,m_min.y,m_min.z);
  m_rbn = glm::dvec3(m_max.x,m_min.y,m_min.z);
}

void Box::TransformBox(){
  m_ltf = glm::dvec3(m_transform * glm::dvec4(m_ltf,1.0));
  m_rtf = glm::dvec3(m_transform * glm::dvec4(m_rtf,1.0));
  m_lbf = glm::dvec3(m_transform * glm::dvec4(m_lbf,1.0));
  m_rbf = glm::dvec3(m_transform * glm::dvec4(m_rbf,1.0));
  m_ltn = glm::dvec3(m_transform * glm::dvec4(m_ltn,1.0));
  m_rtn = glm::dvec3(m_transform * glm::dvec4(m_rtn,1.0));
  m_lbn = glm::dvec3(m_transform * glm::dvec4(m_lbn,1.0));
  m_rbn = glm::dvec3(m_transform * glm::dvec4(m_rbn,1.0));
  m_min = glm::dvec3(std::min
		     (std::min(std::min(m_ltf.x,m_rtf.x),std::min(m_lbf.x,m_rbf.x)),
		      std::min(std::min(m_ltn.x,m_rtn.x),std::min(m_lbn.x,m_rbn.x))),
		     std::min
		     (std::min(std::min(m_ltf.y,m_rtf.y),std::min(m_lbf.y,m_rbf.y)),
		      std::min(std::min(m_ltn.y,m_rtn.y),std::min(m_lbn.y,m_rbn.y))),
		     std::min
		     (std::min(std::min(m_ltf.z,m_rtf.z),std::min(m_lbf.z,m_rbf.z)),
		      std::min(std::min(m_ltn.z,m_rtn.z),std::min(m_lbn.z,m_rbn.z))));  
  m_max = glm::dvec3(std::max
		     (std::max(std::max(m_ltf.x,m_rtf.x),std::max(m_lbf.x,m_rbf.x)),
		      std::max(std::max(m_ltn.x,m_rtn.x),std::max(m_lbn.x,m_rbn.x))),
		     std::max
		     (std::max(std::max(m_ltf.y,m_rtf.y),std::max(m_lbf.y,m_rbf.y)),
		      std::max(std::max(m_ltn.y,m_rtn.y),std::max(m_lbn.y,m_rbn.y))),
		     std::max
		     (std::max(std::max(m_ltf.z,m_rtf.z),std::max(m_lbf.z,m_rbf.z)),
		      std::max(std::max(m_ltn.z,m_rtn.z),std::max(m_lbn.z,m_rbn.z))));
}

bool Box::Intersects(Ray* ray, Intersection* i){
  std::cout << "box intersection not implemented" << std::endl;
  return false;
}

bool Box::IntersectsP(Ray* ray){
  double tmin,tmax,tymin,tymax,tzmin,tzmax;
  glm::dvec4 newMin = glm::dvec4(m_min,1.0);
  glm::dvec4 newMax = glm::dvec4(m_max,1.0);
  //std::cout << "newMax:" << newMax.x <<","<<newMax.y<<","<<newMax.z << std::endl;
  glm::dvec3 rayDir = ray->GetD();
  glm::dvec3 rayOrigin = ray->Getp0();
  if (rayDir.x >= 0) {
    tmin = (newMin.x - rayOrigin.x) / rayDir.x;
    tmax = (newMax.x - rayOrigin.x) / rayDir.x;
  }
  else {
    tmax = (newMin.x - rayOrigin.x) / rayDir.x;
    tmin = (newMax.x - rayOrigin.x) / rayDir.x;
  }
  if (rayDir.y >= 0) {
    tymin = (newMin.y - rayOrigin.y) / rayDir.y;
    tymax = (newMax.y - rayOrigin.y) / rayDir.y;
  }
  else {
    tymax = (newMin.y - rayOrigin.y) / rayDir.y;
    tymin = (newMax.y - rayOrigin.y) / rayDir.y;
  }
  if ((tmin > tymax) || (tymin > tmax)){
    return false;
  }
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;
  if (rayDir.z >= 0) {
    tzmin = (newMin.z - rayOrigin.z) / rayDir.z;
    tzmax = (newMax.z - rayOrigin.z) / rayDir.z;
  }
  else {
    tzmax = (newMin.z - rayOrigin.z) / rayDir.z;
    tzmin = (newMax.z - rayOrigin.z) / rayDir.z;
  }
  if ((tmin > tzmax) || (tzmin > tmax)){
    return false;
  }
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;
  if ((tmin > 999999) || (tmax < -999999)){
    return false;
  }  
  return true;
}


