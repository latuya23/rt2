#ifndef SPHERE_H_
#define SPHERE_H_

#include "Primitive.h"
#include <glm/gtc/type_ptr.hpp>
class Sphere :public Primitive{
public:
	Sphere();
	Sphere(glm::dvec3 pos, double r, Material m, glm::dmat4 inverse, glm::dmat4 transform, glm::dmat4 invT);
	bool Intersects(Ray *r, Intersection *i);
	bool IntersectsP(Ray *r, Intersection *i);
	void print();
	int GetSphereId(){return m_id;}
	virtual ~Sphere();
	static int next_sphere_id(){
			next_id++;
			return next_id;
		}
private:
	double SolveQuadratic(double a, double b, double c);
	double SolveQuadratic2(double a, double b, double c);
	double SolveQuadratic3(double a, double b, double c);

	static int next_id;
	int m_id;
	double radius;
	glm::dvec3 m_pos;
	glm::dmat4 m_inverse;
	glm::dmat4 m_transform;
	glm::dmat4 m_invT;
	bool first;
};

#endif /* SPHERE_H_ */
