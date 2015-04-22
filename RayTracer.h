#ifndef RAYTRACER_H_
#define RAYTRACER_H_
#include "Color.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>
#include "DirectionalLight.h"
#include "PointLight.h"
#include <math.h>

class RayTracer {
public:

	RayTracer();
	RayTracer(int maxD);
	virtual ~RayTracer();
	void SetDepth(int maxD);
	int GetMaxDepth(){return m_Depth;}
	Ray CreateReflectRay(glm::dvec3 rDir, glm::dvec3 surfNormal, glm::dvec3 startP);
	Ray CreateRefractRay(glm::dvec3 rDir, glm::dvec3 surfNormal, glm::dvec3 startP);
	void traceRay(Ray *r, int depth, Color* tColor);
	void addTriangle(Triangle tv);
	void addSphere(Sphere s);
	void AddLight(Light* l);
	void printTriangles();
	void printSpheres();
	void PrintLight();

	//  do shading calculation
	// Li(Kd max(li*n,0)+Ks(n*hi)^shininess) stars are dots
	// Li = light color
	// Kd = diffuse
	// li = light direction
	// n = surface normal
	// Ks = specular
	// hi = half angle vector for the light
	// s = shininess
	Color Shading(Color lColor,Color diffuse,Color specular, glm::dvec3 lightDir,
			glm::dvec3 normal,glm::dvec3 fromEye,double s);

private:
	std::vector<Triangle> myTriangles;
	std::vector<Sphere> mySpheres;
	std::vector<Light*> myLights;
	int m_Depth;
	bool isCloser(Ray *r, Intersection i1, Intersection i2);
	bool check4Intersection(Ray* ray);
};

#endif /* RAYTRACER_H_ */
