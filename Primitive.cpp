#include "Primitive.h"

int Primitive::next_prim_id = 0;
Primitive::Primitive() {
  m_prim_id = Primitive::next_primitive_id();
}

void Primitive::print(){
	printf("i am alive!\n");
}


Primitive::~Primitive() {
	// TODO Auto-generated destructor stub
}
