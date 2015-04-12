#ifndef SPHERE_H_
#define SPHERE_H_

#include "Primitive.h"
#include <glm/gtc/type_ptr.hpp>
class Sphere :public Primitive{
public:
	Sphere();
	Sphere(glm::vec3 pos, double r, Material m, glm::mat4 inverse, glm::mat4 transform, glm::mat4 invT);
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
	glm::vec3 m_pos;
	glm::mat4 m_inverse;
	glm::mat4 m_transform;
	glm::mat4 m_invT;
	bool first;
};

#endif /* SPHERE_H_ */
