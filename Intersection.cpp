#include "Intersection.h"

Intersection::Intersection() {
	// TODO Auto-generated constructor stub

}

Intersection::Intersection(vec3 pos, Material m, double t, vec3 n, int p_id){
	position=pos;
	m_material=m;
	m_t=t;
	normal=n;
	m_p_id = p_id;
}

Intersection::Intersection(vec3 pos, Material m, double t, vec3 n){
	position = pos;
	m_material= m;
	m_t= t;
	normal=n;
	m_p_id=-1;
}

Intersection::~Intersection() {
	// TODO Auto-generated destructor stub
}

void Intersection::SetNormal(vec3 n){
	normal = n;
}
