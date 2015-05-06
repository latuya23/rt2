/*
 * Carlos Macias
 * carlos.macias23@gmail.com
 * Model.h header for model class - a data structure to represent objects to be drawn
 * inherits from primitive
 * it has a bounding volume object
 */
#ifndef _MODEL_H_
#define _MODEL_H_
#include "FaceList.h"
#include "Primitive.h"
#include "Sphere.h"
#include "Box.h"
#include "Triangle.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

class Model :public Primitive{
 public:
  FaceList* faceList;
  std::vector<Triangle*>* m_triangles;
  glm::dvec3 m_modelCenter;
  glm::dvec3 m_mins;
  glm::dvec3 m_maxs;
  std::string m_fName;
  Sphere* m_sphereBV;
  Box* m_boxBV;
  Model(const char* fileName, Material m, glm::dmat4 transfrom,bool ccw);
  ~Model();
  bool readModel(bool ccwVerts);
  void setCenter(glm::dvec3 vec);
  void setModelTransform(glm::dmat4 mat);
  double getBSphereRadius();
  virtual bool IntersectsP(Ray* ray);
  virtual bool Intersects(Ray* ray, Intersection* i);
  virtual void Print();
 private:
  bool IntersectsPBV(Ray* ray);
  bool IntersectsPTriangles(Ray* ray);
  bool IntersectsTriangles(Ray* ray, Intersection* i);
  void CreateTriangles();
  bool IsCloser(Intersection t1, Intersection t2);
  void CenterAt0NScale21();
};

#endif /*_MODEL_H_*/
