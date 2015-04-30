/*
 * Carlos Macias
 * carlos.macias23@gmail.com
 * FaceList class header- a data structure to store vertices
 * and other info from PLY objs 
 */
#ifndef _FACELIST_H_
#define _FACELIST_H_

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <glm/glm.hpp>

class FaceList {
public:
  // array of vertices
  glm::dvec3 **vertices;
  // array of face indices
  glm::uvec3 **faces;
  // vertex count
  int vc;
  // face count
  int fc;
  // The face's surface normal
  glm::dvec3 **f_normals;
  glm::dvec3 **v_normals;
  FaceList(int vertexCount,int faceCount);
  FaceList();
  ~FaceList();
};
#endif /* FACELIST_H_ */
