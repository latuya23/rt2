#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "Ray.h"
#include "nv/nv_math.h"
#include "Intersection.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Material.h"

class Primitive {
public:
	Primitive();
	Primitive(vec3 v);
	virtual ~Primitive();
	virtual void print();
	virtual bool intersects(Ray *r, Intersection *i);
	Material m_material;
	Material GetMaterial(){return m_material;}
};

#endif /* PRIMITIVE_H_ */
