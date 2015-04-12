#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Primitive.h"

class Triangle : public Primitive {
public:
	Triangle();
	Triangle(glm::vec3 verts[3], glm::vec3 norm, Material m);
	Triangle(glm::vec3 verts[3], glm::vec3 norms[3], Material m);

	virtual ~Triangle();
	void print();
	bool Intersects(Ray *r, Intersection *i);
	bool IntersectsP(Ray *r, Intersection *i);
	void printVector(glm::vec3 v);
	void setFaceNormal(glm::vec3 n);

private:
	glm::vec3 vertices[3];
	glm::vec3 normals[3];
	glm::vec3 face_normal;
};

#endif /* TRIANGLE_H_ */
