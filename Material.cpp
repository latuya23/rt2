#include "Material.h"

Material::Material() {
	//set up the defaults when a material is created
}

Material::Material(BRDF aBRDF) {
	constantBRDF=aBRDF;
}
Material::~Material() {
	// TODO Auto-generated destructor stub
}
