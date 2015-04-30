/*
 * Carlos Macias
 * carlos.macias23@gmail.com
 * Box.h is the header for the class that represents a box object
 * inherits from Primitive 
 * it has a min vector and a max vector.
 * it has the AABBintersection with ray method
 */
#ifndef _BOX_H_
#define _BOX_H_
#include <glm/glm.hpp>
#include "Primitive.h"
#include "Ray.h"
class Box : public Primitive{
 public:
  glm::dvec3 m_min;
  glm::dvec3 m_max;
  //-zfar:f,znear:n,ytop:t,-ybottom:b,-xleft:l,xright:r
  glm::dvec3 m_ltf;
  glm::dvec3 m_rtf;
  glm::dvec3 m_lbf;
  glm::dvec3 m_rbf;
  glm::dvec3 m_ltn;
  glm::dvec3 m_rtn;
  glm::dvec3 m_lbn;
  glm::dvec3 m_rbn;
  int m_boxId;
  void *m_quadricObj;
  Box(glm::dvec3 minv,glm::dvec3 maxv);
  Box(glm::dvec3 minv,glm::dvec3 maxv, glm::dmat4 modelM);
  ~Box();
  virtual bool IntersectsP(Ray* ray);
  virtual bool Intersects(Ray* ray, Intersection* i);
  virtual void Print();
  void TransformBox();
  
 private:
  static int next_box_id();
  static int next_id;
  void SetVertices();
};

#endif /* _BOX_H_ */


