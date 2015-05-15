#ifndef KDNODE_H_
#define KDNODE_H_

#include <vector>
#include "Triangle.h"
#include "Box.h"

class KdNode {
 public:
  Box* m_boxBV;
  KdNode* leftChild;
  KdNode* rightChild;
  std::vector<Triangle*> m_triangles;
  KdNode();
  KdNode* buildTree(std::vector<Triangle*>& tris, int depth);
  bool IntersectsKDTree(Ray* ray, Intersection* isect);
  bool IsCloser(Intersection t1, Intersection t2);
  void Print();
};
#endif /* KDNODE_H_ */
