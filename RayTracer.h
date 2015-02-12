#ifndef RAYTRACER_H_
#define RAYTRACER_H_
#include "Color.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>
#include "DirectionalLight.h"
#include "PointLight.h"
#include <math.h>

using namespace std;

class RayTracer {
public:

	RayTracer();
	RayTracer(int maxD);
	virtual ~RayTracer();
	void SetDepth(int maxD);
	int GetMaxDepth(){return m_Depth;}
	Ray CreateReflectRay(vec3 rDir, vec3 surfNormal, vec3 startP);
	Ray CreateRefractRay(vec3 rDir, vec3 surfNormal, vec3 startP);
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
	Color Shading(Color lColor,Color diffuse,Color specular, vec3 lightDir,
			vec3 normal,vec3 fromEye,double s);

private:
	vector<Triangle> myTriangles;
	vector<Sphere> mySpheres;
	vector<Light*> myLights;
	int m_Depth;
	bool isCloser(Ray *r, Intersection i1, Intersection i2);
};

#endif /* RAYTRACER_H_ */
