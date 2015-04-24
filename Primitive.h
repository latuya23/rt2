#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "Ray.h"
#include "Intersection.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Material.h"
#include <glm/glm.hpp>

class Primitive {
 protected:
  Material m_material;
  static int next_prim_id;
  int m_prim_id;
 public:
  Primitive();
  virtual ~Primitive();
  static int next_primitive_id(){
    next_prim_id++;
    return next_prim_id;
  }
  virtual void print() = 0;
  virtual bool Intersects(Ray *ray, Intersection *inters) = 0;
  virtual bool IntersectsP(Ray* ray) = 0;
  Material GetMaterial(){return m_material;}
};

#endif /* PRIMITIVE_H_ */
