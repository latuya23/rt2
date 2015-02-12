#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Primitive.h"

class Triangle : public Primitive {
public:
	Triangle();
	Triangle(vec3 verts[3], vec3 norm, Material m);
	Triangle(vec3 verts[3], vec3 norms[3], Material m);

	virtual ~Triangle();
	void print();
	bool Intersects(Ray *r, Intersection *i);
	bool IntersectsP(Ray *r, Intersection *i);
	void printVector(vec3 v);
	void setFaceNormal(vec3 n);

private:
	vec3 vertices[3];
	vec3 normals[3];
	vec3 face_normal;
};

#endif /* TRIANGLE_H_ */
