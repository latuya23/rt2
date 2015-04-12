#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <assert.h>
#include <math.h>
#include <fstream>
#include "Camera.h"
#include "Sampler.h"
#include "Triangle.h"
#include "RayTracer.h"
#include <vector>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

class Parser{
public:
void initialparse(std::ifstream &inputfile, int* sizex, int* sizey);
void parsefile(std::ifstream &inputfile, Camera *cam, RayTracer *tracer, int* maxD);
};
#endif /*PARSER_H_*/
