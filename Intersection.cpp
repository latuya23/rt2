#include "Intersection.h"

Intersection::Intersection() {
	// TODO Auto-generated constructor stub

}

Intersection::Intersection(glm::dvec3 pos, Material m, double t, glm::dvec3 n, int p_id){
	position=pos;
	m_material=m;
	m_t=t;
	normal=n;
	m_p_id = p_id;
}

Intersection::Intersection(glm::dvec3 pos, Material m, double t, glm::dvec3 n){
	position = pos;
	m_material= m;
	m_t= t;
	normal=n;
	m_p_id=-1;
}

Intersection::~Intersection() {
	// TODO Auto-generated destructor stub
}

void Intersection::SetNormal(glm::dvec3 n){
	normal = n;
}

void Intersection::Print(){
  std::cout<< "ipos: " << glm::to_string(position)<<std::endl;
  std::cout<< "t: " << m_t << std::endl;
  std::cout<< "normal: " << glm::to_string(normal)<<std::endl;
  std::cout<< "Material: ";
  m_material.GetBRDF().PrintBRDF();
  std::cout<<std::endl;
}
