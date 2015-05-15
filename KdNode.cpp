//http://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/
//modified version of the code presented on the above link
#include "KdNode.h"

KdNode::KdNode(){
}

KdNode* KdNode::buildTree(std::vector<Triangle*>& tris, int depth) {
  KdNode* node = new KdNode();
  node->m_triangles = tris;
  node->leftChild = NULL;
  node->rightChild = NULL;
  node->m_boxBV = new Box();
  //node->Print();

  if (tris.size() == 0){
    return node;
  }
  if (tris.size() == 1) {
    node->m_boxBV = tris[0]->m_boxBV;
    node->leftChild = new KdNode();
    node->rightChild = new KdNode();
    node->leftChild->m_triangles = std::vector<Triangle*>();
    node->rightChild->m_triangles = std::vector<Triangle*>();
    return node;
  }

  //get box surrounding all triangles
  //node->m_boxBV = tris[0]->m_boxBV;
  for (unsigned int i=0; i < tris.size(); i++){
    node->m_boxBV = node->m_boxBV->Union(*(tris[i]->m_boxBV));
  }
  glm::dvec3 midPoint(0.0);
  for (unsigned int i = 0; i < tris.size(); i++){
    //find midpoint of all triangles
    midPoint = midPoint + (tris[i]->m_boxBV->Center() * (1.0 / tris.size()));
  }
  std::vector<Triangle*> left_tris;
  std::vector<Triangle*> right_tris;
  int axis = node->m_boxBV->MaxExtent();
  for(unsigned int i=0; i < tris.size();i++){
    //split triangles based on their midpoints avg
    switch(axis){
      case 0://x axis
	if (midPoint.x >= tris[i]->m_boxBV->Center().x){
	  right_tris.push_back(tris[i]);
	}
	else{
	  left_tris.push_back(tris[i]);
	}
      case 1:// y axis
	if (midPoint.y >= tris[i]->m_boxBV->Center().y){
	  right_tris.push_back(tris[i]);
	}
	else{
	  left_tris.push_back(tris[i]);
	}
      case 2:// z axis
	if (midPoint.z >= tris[i]->m_boxBV->Center().z){
	  right_tris.push_back(tris[i]);
	}
	else{
	  left_tris.push_back(tris[i]);
	}
    }
  }
  if (left_tris.empty() && !right_tris.empty()){
    left_tris = right_tris;
  }
  if (right_tris.empty() && !left_tris.empty()){
    right_tris = left_tris;
  }
  int matches = 0;
  for (unsigned int i=0; i < left_tris.size(); i++){
    for (unsigned int j=0; j < right_tris.size();j++){
      if (left_tris[i] == right_tris[i]){
	matches++;
      }
    }
  }
  if ((float)matches / left_tris.size() < .5 &&
      (float)matches / right_tris.size() < .5) {
    node->leftChild = buildTree(left_tris, depth+1);
    node->rightChild = buildTree(right_tris, depth+1);
    //std::cout << "depth: " << depth << std::endl;
  }
  else{
    node->leftChild = new KdNode();
    node->rightChild = new KdNode();
    node->leftChild->m_triangles = std::vector<Triangle*>();
    node->rightChild->m_triangles = std::vector<Triangle*>();
  }
  //node->Print();
  return node;  
}
Material tempM;
bool KdNode::IntersectsKDTree(Ray* ray, Intersection* isect){
  if (m_boxBV->IntersectsP(ray)){
    bool foundAny = false;
    Intersection closest = Intersection(glm::dvec3(0),tempM,
					10000.0,glm::dvec3(0));
    Intersection temp;
    if (leftChild->m_triangles.size() > 0 ||
	rightChild->m_triangles.size() > 0 ){
      bool foundAnyLeft = leftChild->IntersectsKDTree(ray,&temp);
      if (IsCloser(temp,closest)){
	closest = temp;
      }
      bool foundAnyRight = rightChild->IntersectsKDTree(ray,&temp);
      if (IsCloser(temp,closest)){
	closest = temp;
      }
      *isect = closest;
      return foundAnyLeft || foundAnyRight;
    }
    else {
      //leaves
      for (unsigned int i=0; i < m_triangles.size(); i++){
	if(m_triangles[i]->Intersects(ray,&temp)){
	  foundAny = true;
	  if (IsCloser(temp,closest)){
	    closest = temp;
	  }
	}
      }
      *isect = closest;
      return foundAny;
    }
  }
  return false;
}

bool KdNode::IsCloser(Intersection t1, Intersection t2){
  if(t1.GetT() < t2.GetT() && t2.GetT()>.01 && t1.GetT()>.01)
    return true;
  return false;
}

void KdNode::Print(){
  std::cout << "KdNode: "<< std::endl;
  m_boxBV->Print();
  std::cout << "tris # : " << m_triangles.size() << std::endl;
}
