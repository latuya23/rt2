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
  Ray CreateReflectRay(glm::dvec3 rDir,glm::dvec3 surfNormal,glm::dvec3 startP);
  Ray CreateRefractRay(glm::dvec3 rDir, glm::dvec3 surfNormal,
		       glm::dvec3 startP,int depth);
  void traceRay(Ray *r, int depth, Color* tColor);
  void AddPrimitive(Primitive* prim);
  void AddLight(Light* l);
  void PrintPrims();
  void PrintLight();
  void SetDebugNoShadows(bool noShadows);
  void SetDebugNoLightButKaKe(bool kaKeOnly);
  void SetDebugNoReflections(bool noRefl);
  void SetDebugNoRefractions(bool noRefr);
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
  bool avoidReflections;
  bool avoidRefractions;
  bool avoidShadows;
  bool avoidAllLightButKaKe;
  std::vector<Primitive*> myPrims;
  std::vector<Light*> myLights;
  int m_Depth;
  bool isCloser(Ray *r, Intersection i1, Intersection i2);
  bool check4Intersection(Ray* ray);
  glm::dvec3 Refract(glm::dvec3 I, glm::dvec3 N, double eta);
};

#endif /* RAYTRACER_H_ */
