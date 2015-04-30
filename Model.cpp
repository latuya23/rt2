/*
 * Carlos Macias
 * carlos.macias23@gmail.com
 * Model class - a data structure to represent a model to be drawn
 * inherits from primitive
 * it has a bounding volume object
 */
#include "Model.h"
#include "glm/gtx/string_cast.hpp"
#include <fstream>
#include <sstream> 
#include <cmath>

Model::Model(const char* fileName, Material m, glm::dmat4 transform, bool ccw){
  faceList = NULL;
  m_triangles = NULL;
  m_mins = glm::dvec3(std::numeric_limits<int>::max());
  m_maxs = glm::dvec3(std::numeric_limits<int>::min());
  m_transform = transform;
  m_invTT = glm::inverseTranspose(m_transform);
  m_material = m;
  m_fName = fileName;
  if (readModel(ccw)){
    std::cout << "read model successfully"<<std::endl;
  }
}

Model::~Model(){
  delete m_boxBV;
  delete m_sphereBV;
  for (unsigned int i = 0; i < m_triangles->size();i++){
    delete (*m_triangles)[i];
  }
  delete m_triangles;
  delete faceList;
}

void Model::setModelTransform(glm::dmat4 mat){
  m_transform = mat;
  //m_sphereBV.m_transform = mat;
  //m_boxBV->m_transform = mat;
}

void Model::setCenter(glm::dvec3 vec){
  m_modelCenter = vec;
  //m_sphereBV.m_pos = vec;
}

double Model::getBSphereRadius(){
  return m_sphereBV->GetSphRadius();
}

bool Model::Intersects(Ray* ray, Intersection* i){
  if (IntersectsPBV(ray)){
    return IntersectsTriangles(ray, i);
  }
  return false;
}

bool Model::IntersectsP(Ray* ray){
  if (IntersectsPBV(ray)){
    return IntersectsPTriangles(ray);
  }
  return false;
}

bool Model::IntersectsPBV(Ray* ray){
  return m_boxBV->IntersectsP(ray);
}

bool Model::IntersectsTriangles(Ray* ray, Intersection* inters){
  bool foundAny = false;
  Intersection temp;
  Intersection closest = Intersection(glm::dvec3(0),m_material ,
			 100000.0, glm::dvec3(0));
  for (unsigned int i = 0; i < m_triangles->size(); i++){
    if ((*m_triangles)[i]->Intersects(ray,&temp)){
      foundAny = true;
      //std::cout << "the intersect happened at: " << i << std::endl;
      //temp.Print();
      //(*m_triangles)[i]->Print();
      if(IsCloser(temp,closest)){
	closest = temp;
      }
    }
  }
  //std::cout << "the intersect happened at: " << std::endl;
  //closest.Print();
  //std::cout << "found " << foundAny << " intersections"<<std::endl;
  *inters = closest;
  return foundAny;
}
bool Model::IsCloser(Intersection t1, Intersection t2){
  if(t1.GetT() < t2.GetT() && t2.GetT()>.01 && t1.GetT()>.01)
    return true;
  return false;
}

bool Model::IntersectsPTriangles(Ray* ray){
  for (unsigned int i = 0; i < m_triangles->size(); i++){
    if ((*m_triangles)[i]->IntersectsP(ray)){
      return true;
    }
  }
  return false;
}

void Model::calcBSphere(glm::dvec3 *center, double *radius, FaceList *fl){
  double maxDistance = 0.0;
  for( int i = 0; i < fl->vc-1; i++ ){
    for(int j = i + 1; j < fl->vc; j++){
      glm::dvec3 a = *fl->vertices[i];
      glm::dvec3 b = *fl->vertices[j];
 
      glm::dvec3 temp = a-b;
      double distance = glm::dot(temp,temp);
      if( distance > maxDistance){
       double t = .5;
       *center = glm::dvec3((a+b)*t);
        *radius = sqrt(distance) * 0.5;
        maxDistance = distance;
      }
    }
  }
  //std::cout << "center: "<<std::endl;
  //std::cout << *center << std::endl;
  //std::cout << m_modelCenter.x << "," << m_modelCenter.y <<","<<m_modelCenter.z << std::endl;
}

void Model::Print(){
  std::cout << "Model #: " << m_prim_id << std::endl;
  std::cout << "filename: " << m_fName << std::endl;
  std::cout << "pos: " << glm::to_string(m_modelCenter) << std::endl;
  //std::cout << ": " << m_prim_id << std::endl;
  
}

bool Model::readModel (bool ccwVerts){
  int vIndex = 0;
  int fIndex = 0;
  int vCount = 0;
  int fCount = 0;
  std::string line;
  std::string filename = "./models/";
  filename.append(m_fName);
  std::ifstream modelStream(filename.c_str());
  if (!modelStream.is_open()){
    std::cerr << "File: " << filename << " could not be opened." << std::endl;
    exit(EXIT_FAILURE);
  }
  while(getline(modelStream,line)){
    if (line.find("ply") != std::string::npos ||
	line.find("format") != std::string::npos ||
	line.find("comment") != std::string::npos ||
	line.find("property") != std::string::npos ||
	line.find("end_header") != std::string::npos) {
      /*ignore this lines are not used*/    
    }
    else if (line.find("element vertex ") != std::string::npos){
      std::istringstream vcLineStream(line);
      std::string notNeeded;
      vcLineStream >> notNeeded >> notNeeded >> vCount;
      if (vCount == 0){
	std::cerr << "Number of vertices not provided" << std::endl;
	exit(EXIT_FAILURE);
      }
    }
    else if (line.find("element face ") != std::string::npos){
      std::istringstream fcLineStream(line);
      std::string notNeeded;
      fcLineStream >> notNeeded >> notNeeded >> fCount;
      if (fCount == 0){
	std::cerr << "Number of faces not provided" << std::endl;
	exit(EXIT_FAILURE);
      }
    }
    else /*read vertices and faces*/ {
      std::istringstream lineStream(line);
      if (faceList == NULL){
	if (!(faceList = new FaceList(vCount,fCount))){
	  std::cerr << "Could not allocate facelist." << std::endl;
	  exit(EXIT_FAILURE);
	}
      }
      if (vIndex < vCount){
	//readVertex
	double x,y,z;
	lineStream >> x >> y >> z ;	
	m_maxs.x = std::max(m_maxs.x,x);
	m_maxs.y = std::max(m_maxs.y,y);
	m_maxs.z = std::max(m_maxs.z,z);
	m_mins.x = std::min(m_mins.x,x);
	m_mins.y = std::min(m_mins.y,y);
	m_mins.z = std::min(m_mins.z,z);
	*faceList->vertices[vIndex] = glm::dvec3(x,y,z);
	vIndex++;
      }
      else if (vIndex == vCount && fIndex < fCount){
	//readFace
	int sides,a,b,c;
	lineStream >> sides >> a >> b >> c ;
	if (sides != 3){
	  std::cerr << "Not a triangle." << std::endl;
	  exit(EXIT_FAILURE);
	}
        *faceList->faces[fIndex] = glm::uvec3(a,b,c);
	glm::dvec3 fnormal(0.0);
	if (ccwVerts){
	  fnormal = glm::normalize 
		  (glm::cross
		   (*faceList->vertices[c] - *faceList->vertices[b],
		    *faceList->vertices[a] - *faceList->vertices[b]));	
	}
	else{//CW vertices
	  fnormal = glm::normalize 
		  (glm::cross
		   (*faceList->vertices[a] - *faceList->vertices[b],
		    *faceList->vertices[c] - *faceList->vertices[b]));	
	}
	*faceList->f_normals[fIndex] = fnormal;
	*faceList->v_normals[faceList->faces[fIndex]->x] = 
	  *faceList->v_normals[faceList->faces[fIndex]->x] + fnormal;
	*faceList->v_normals[faceList->faces[fIndex]->y] = 
	  *faceList->v_normals[faceList->faces[fIndex]->y] + fnormal;
	*faceList->v_normals[faceList->faces[fIndex]->z] = 
	  *faceList->v_normals[faceList->faces[fIndex]->z] + fnormal;
	fIndex++;
      }
      else {
	std::cerr << "Number of entries exceeds numbers provided" << std::endl;
	std::cerr << "Extra line: "<< line << std::endl;
	exit(EXIT_FAILURE);
      }
    }
  }
  modelStream.close();
  //std::cout << "got here" << std::endl;
  //glm::dvec3 halfVector = (m_maxs-m_mins)*.5;
  //m_modelCenter = m_mins + halfVector;
  //double sphRadius = glm::length(halfVector);
  double sphRadius;
  calcBSphere(&m_modelCenter, &sphRadius,faceList);
  //std::cout << "center: " << m_modelCenter.x <<","<<m_modelCenter.y<<","<<m_modelCenter.z << std::endl;
  std::cout << "radius: " << sphRadius << std::endl;
  //exit(0);
  //std::cout << "bSph calc"<<std::endl;
  // normalize the v_normals and make modelview trans of obj = identity matrix
  CenterNScale(m_modelCenter,1.0/sphRadius);
  CreateTriangles();
  Print();
  return true;
}

void Model::CenterNScale(glm::dvec3 centerAt,double scaleFactor){
  for( int i = 0; i < faceList->vc; i++ ){
    *faceList->v_normals[i] = glm::normalize(*faceList->v_normals[i]);
    *faceList->vertices[i] = (*faceList->vertices[i] - centerAt) * scaleFactor;
  }
  //move max and min
  m_maxs = (m_maxs - centerAt) * scaleFactor;
  m_mins = (m_mins - centerAt) * scaleFactor;
  // move center to 0 and create bV with 1 radius
  std::cout << "model center: " <<  glm::to_string(m_modelCenter)<<std::endl;;
  m_modelCenter = centerAt - centerAt; //move to 0
  std::cout << "model center: " << glm::to_string(m_modelCenter)<<std::endl;
  m_sphereBV= new Sphere(centerAt,1.0);//create unit sphere BV
  m_boxBV = new Box(m_mins,m_maxs,m_transform);//create box BV
}

void Model::CreateTriangles(){
  m_material.GetBRDF().PrintBRDF();
  m_triangles = new std::vector<Triangle*>();
  m_boxBV->Print();
  m_boxBV->TransformBox();
  m_boxBV->Print();
  for (int i = 0; i < faceList->fc; i++){
    glm::uvec3 sides = *faceList->faces[i];
    glm::dvec3 verts[3];
    glm::dvec3 normal;
    verts[0] = //*faceList->vertices[sides.x];
      glm::dvec3(m_transform *
		 glm::dvec4(*faceList->vertices[sides.x],1.0));
  verts[1] = //*faceList->vertices[sides.y];
    glm::dvec3(m_transform *
	       glm::dvec4(*faceList->vertices[sides.y],1.0));
  verts[2] = //*faceList->vertices[sides.z];
    glm::dvec3(m_transform *
	       glm::dvec4(*faceList->vertices[sides.z],1.0));
  normal = //glm::normalize (glm::cross(verts[0] - verts[1],
    //				verts[2] - verts[1]));
    glm::normalize(glm::dvec3(m_invTT *
			      glm::dvec4(*faceList->f_normals[i],0)));
    
    Triangle* triangle = new Triangle(verts,normal,m_material);
    
    m_triangles->push_back(triangle);
    //triangle->Print();
  }
}

