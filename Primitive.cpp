#include "Primitive.h"

Primitive::Primitive() {
	
}

Primitive::Primitive(vec3 v) {

}

void Primitive::print(){
	printf("i am alive!\n");
}


Primitive::~Primitive() {
	// TODO Auto-generated destructor stub
}

bool Primitive::intersects(Ray *r, Intersection *i){
	
	return true;
}
