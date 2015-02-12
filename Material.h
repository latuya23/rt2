#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "BRDF.h"

class Material {
private:
	BRDF constantBRDF;
public:
	Material();
	Material(BRDF aBRDF);
	virtual ~Material();
	BRDF GetBRDF(){return constantBRDF;}
};

#endif /* MATERIAL_H_ */
