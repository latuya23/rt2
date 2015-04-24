#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Primitive.h"

class Triangle : public Primitive {
public:
	Triangle(glm::dvec3 verts[3], glm::dvec3 norm, Material m);
	Triangle(glm::dvec3 verts[3], glm::dvec3 norms[3], Material m);
	virtual ~Triangle();
	static int next_triangle_id(){
			next_tri_id++;
			return next_tri_id;
		}
	virtual void print();
	virtual bool Intersects(Ray *r, Intersection *i);
	virtual bool IntersectsP(Ray *r);
	void printVector(glm::dvec3 v);
	void setFaceNormal(glm::dvec3 n);
private:
	static int next_tri_id;
	int m_tri_id;
	glm::dvec3 vertices[3];
	glm::dvec3 normals[3];
	glm::dvec3 face_normal;
};

#endif /* TRIANGLE_H_ */
