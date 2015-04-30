#ifndef SPHERE_H_
#define SPHERE_H_

#include "Primitive.h"
#include <glm/gtc/type_ptr.hpp>
class Sphere :public Primitive{
 public:
  Sphere(glm::dvec3 pos, double radius);
  Sphere(glm::dvec3 pos, double r, Material m, glm::dmat4 inverse, glm::dmat4 transform, glm::dmat4 invT);
  virtual ~Sphere();
  virtual bool Intersects(Ray *ray, Intersection *i);
  virtual bool IntersectsP(Ray *ray);
  void Print();
  int GetSphereId(){return m_sph_id;}
  double GetSphRadius(){return m_radius;}
  void SetSphRadius(double radius){m_radius=radius;}
  static int next_sphere_id(){
    next_sph_id++;
    return next_sph_id;
  }
 protected:
  static int next_sph_id;
  int m_sph_id;
  double m_radius;
  glm::dvec3 m_pos;
  glm::dmat4 m_inverse;
  glm::dmat4 m_transform;
  glm::dmat4 m_invT;
};

#endif /* SPHERE_H_ */
