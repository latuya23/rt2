#include "Sphere.h"

#define MIN_THRESHOLD .001
int Sphere::next_sph_id = 0;

Sphere::Sphere(glm::dvec3 pos, double r, Material m,
	       glm::dmat4 inverse, glm::dmat4 transform, glm::dmat4 invT){
  m_pos = pos;
  m_radius = r;
  m_material = m;
  m_inverse = inverse;
  m_transform = transform;
  m_invT=invT;
  m_sph_id= Sphere::next_sphere_id();
}

//3d game engine design pg 699
//pbr pg 118
bool Sphere::Intersects(Ray *ray, Intersection *i){
  glm::dvec3 rDirOSU = glm::dvec3(m_inverse * glm::dvec4(ray->GetD(),0.0));
  double magnitude = glm::length(rDirOSU);
  glm::dvec3 rDirOS = glm::normalize(rDirOSU);
  glm::dvec3 rStartRealPOS = glm::dvec3(m_inverse * glm::dvec4(ray->Getp0(),1.0));
  glm::dvec3 delta = rStartRealPOS - m_pos;
  double a0 = glm::dot(delta,delta) - m_radius * m_radius;
  double a1 = glm::dot(rDirOS,delta);
  double discr = a1 * a1 - a0;
  double tvalue[2];
  if (discr < 0){
    return false;
  }
  else if (discr >= MIN_THRESHOLD){//2 real roots get closest
    double root = sqrt(discr);
    tvalue[0] = -a1 - root;
    tvalue[1] = -a1 + root;
    if (tvalue[0] > tvalue[1]){
      std::swap(tvalue[0],tvalue[1]);
    }//t0 has the smallest value
    if (tvalue[0] < MIN_THRESHOLD){
      std::swap(tvalue[0],tvalue[1]);
    }//t0 has the smallest value > 0
    if (tvalue[0] < .001 || tvalue[0] > 100000.0){
      return false;
    }
  }
  else {
    tvalue[0] = -a1;
    if (tvalue[0] < MIN_THRESHOLD){
      return false;
    }
  }
  glm::dvec3 inPosOS = rStartRealPOS + (rDirOS * tvalue[0]);
  glm::dvec3 inPosWS = glm::dvec3(m_transform * glm::dvec4(inPosOS,1.0));
  glm::dvec3 normalOS = inPosOS-m_pos; //normal in OS
  glm::dvec3 normalWS = glm::normalize(glm::dvec3(m_invT * glm::dvec4(normalOS,0.0)));
  *i = Intersection (inPosWS, m_material,tvalue[0]/magnitude, normalWS, m_sph_id); //inPoint WS, distance WS, normal WS
  return true;
}

//3d game engine design pg 700-701
bool Sphere::IntersectsP(Ray* ray){
  glm::dvec3 rDirOSU = glm::dvec3(m_inverse * glm::dvec4(ray->GetD(),0.0));
  double magnitude = glm::length(rDirOSU);
  glm::dvec3 rDirOS = glm::normalize(rDirOSU);
  glm::dvec3 rStartPOS = glm::dvec3(m_inverse * glm::dvec4(ray->Getq0(),1.0));
  glm::dvec3 delta = rStartPOS - m_pos;
  double length2SphSqr = glm::dot(delta,delta);
  double a0 = length2SphSqr - (m_radius * m_radius);
  double rayLengthSqr = ray->Gettmax()/magnitude*ray->Gettmax()/magnitude;
  if (a0 <= MIN_THRESHOLD || a0 > rayLengthSqr){
    //ray origin is inside or on the sphere. We don't want to intersect if inside
    //std::cout << "ray origin inside sphere" <<std::endl;
    return false;
  }
  //ray origin is outside the sphere 
  float a1 = glm::dot(rDirOS, delta);
  if (a1 >= MIN_THRESHOLD){
    //ray is directed away from the sphere
    //std::cout << "ray direction away from sphere" << std::endl;
    return false;
  }
  float discr = a1 * a1 - a0;
  return discr >= MIN_THRESHOLD; // if discriminant > 0 we have a hit. we don't care where.
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

void Sphere::print(){
	std::cout<<"\n\n"<<std::endl;
	const float *pSource = (const float*)glm::value_ptr(m_inverse);
	std::cout<<std::endl;
	for(int i = 0; i < 16; i++){
	  std::cout<<pSource[i]<<"\t";
	}
	std::cout<<std::endl;
}
