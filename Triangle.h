#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Primitive.h"

class Triangle : public Primitive {
public:
	Triangle();
	Triangle(glm::dvec3 verts[3], glm::dvec3 norm, Material m);
	Triangle(glm::dvec3 verts[3], glm::dvec3 norms[3], Material m);

	virtual ~Triangle();
	void print();
	bool Intersects(Ray *r, Intersection *i);
	bool IntersectsP(Ray *r);
	void printVector(glm::dvec3 v);
	void setFaceNormal(glm::dvec3 n);

private:
	glm::dvec3 vertices[3];
	glm::dvec3 normals[3];
	glm::dvec3 face_normal;
};

#endif /* TRIANGLE_H_ */
