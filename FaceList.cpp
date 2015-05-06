/*
 * Carlos Macias
 * carlos.macias23@gmail.com
 * FaceList class header- a data structure to store vertices
 * and other info from PLY objs 
 */
#include "FaceList.h"

FaceList::FaceList(){}

FaceList::FaceList(int vertexCount, int faceCount){
  vc = vertexCount;
  fc = faceCount;
  vertices = new glm::dvec3*[vc];
  v_normals = new glm::dvec3*[vc];
  for (int i=0; i<vc;i++){
    vertices[i] = new glm::dvec3(0.0);
    v_normals[i] = new glm::dvec3(0.0);
    //std::cout << "{"
    //	      << colors[i]->x << " " << colors[i]->y << " " << colors[i]->z
    //	      << "}" <<std::endl;
  }
  faces = new glm::uvec3*[fc];
  f_normals = new glm::dvec3*[fc];
  for (int i=0; i<fc;i++){
    faces[i] = new glm::uvec3(0);
    f_normals[i] = new glm::dvec3(0.0);
  }
}

FaceList::~FaceList(){
  for (int i=0; i <vc;i++){
    delete vertices[i];
    delete v_normals[i];
  }
  delete[] vertices;
  delete[] v_normals;
  for(int i = 0; i<fc; i++){
    delete faces[i];
    delete f_normals[i];
  }
  delete[] faces;
  delete[] f_normals;
}



