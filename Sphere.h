#ifndef SPHERE_H_
#define SPHERE_H_

#include "Primitive.h"
class Sphere :public Primitive{
public:
	Sphere();
	Sphere(vec3 pos, double r, Material m, mat4 inverse, mat4 transform, mat4 invT);
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
	vec3 m_pos;
	mat4 m_inverse;
	mat4 m_transform;
	mat4 m_invT;
	bool first;
};

#endif /* SPHERE_H_ */
