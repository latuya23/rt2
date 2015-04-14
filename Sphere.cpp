#include "Sphere.h"
#include "nv_math.h"

Sphere::Sphere() {
  // TODO Auto-generated constructor stub
}

Sphere::Sphere(glm::dvec3 pos, double r, Material m,
	       glm::dmat4 inverse, glm::dmat4 transform, glm::dmat4 invT){
  m_pos = pos;
  radius = r;
  m_material = m;
  m_inverse = inverse;
  m_transform = transform;
  m_invT=invT;
  m_id= Sphere::next_sphere_id();
}

vec3 GetVec3FromGLM (glm::dvec3 v){
  vec3 vNV(0,0,0);
  vNV.x = v.x;
  vNV.y = v.y;
  vNV.z = v.z;
  return vNV;
}

mat4 GetMat4FromGLM(glm::dmat4 m){
  mat4 mat4NV;
  identityMatrix(mat4NV);
  mat4NV.a00 = m[0][0];
  mat4NV.a01 = m[1][0];
  mat4NV.a02 = m[2][0];
  mat4NV.a03 = m[3][0];
  
  mat4NV.a10 = m[0][1];
  mat4NV.a11 = m[1][1];
  mat4NV.a12 = m[2][1];
  mat4NV.a13 = m[3][1];

  mat4NV.a20 = m[0][2];
  mat4NV.a21 = m[1][2];
  mat4NV.a22 = m[2][2];
  mat4NV.a23 = m[3][2];

  mat4NV.a30 = m[0][3];
  mat4NV.a31 = m[1][3];
  mat4NV.a32 = m[2][3];
  mat4NV.a33 = m[3][3];
  return mat4NV;
}
glm::dvec3 GetGLMFromVec3(vec3 v){
  return glm::dvec3(v.x,v.y,v.z);
}

bool Sphere::Intersects(Ray *q, Intersection *i){
  vec3 temp1, temp2, temp3;
  //vec3 initialPoint = GetVec3FromGLM(q->Getq0());
  //mat4 inverseM = GetMat4FromGLM(m_inverse);
  mult(temp1,GetMat4FromGLM(m_inverse),GetVec3FromGLM(q->Getq0()));// //M^-1 * r0 ;r0 of ray World Space to object space
  //vec3 rayDir = GetVec3FromGLM(q->GetD());
  mult_dir(temp2,GetMat4FromGLM(m_inverse),GetVec3FromGLM(q->GetD()));//M^-1 * dir; dir of ray World Space to object space
  //vec3 rayStartP = GetVec3FromGLM(q->Getp0());
  mult(temp3,GetMat4FromGLM(m_inverse),GetVec3FromGLM(q->Getp0()));//M^-1 * p0 ; real p0 of ray World Space to OS
  Ray dtRay(GetGLMFromVec3(temp1),GetGLMFromVec3(temp2),
	    GetGLMFromVec3(temp3),q->Gettmax()); //ray with unnormalized dir in OS
  normalize(temp2);//normalize dir in OS
  Ray tRay (GetGLMFromVec3(temp1),GetGLMFromVec3(temp2),
	    GetGLMFromVec3(temp3),q->Gettmax());//make a ray in OS
  glm::dvec3 qDir = tRay.GetD(); //direction of ray in OS
  glm::dvec3 qminC = tRay.Getp0() - m_pos;// // p0 in OS - center of the sphere in OS
  glm::dvec3 qDir2 = dtRay.GetD(); //direction of ray in OS with unnormalized dir in OS
  glm::dvec3 qminC2 = dtRay.Getp0() - m_pos;// // p0 in OS - center of the sphere in OS
  double a, b, c , d;
  a = (double)glm::dot(qDir, qDir);
  b = (double)2.0*glm::dot(qDir, qminC);
  c = (double)glm::dot(qminC,qminC)- (radius*radius);
  d = SolveQuadratic2(a,b,c);
  if(d < 0 || isnan(d) || d< .0000001 || d>tRay.Gettmax() || d<.01) {
    return false;
  }
  double a2, b2, c2, d2;
  a2 = (double)glm::dot(qDir2, qDir2);
  b2 = (double)2.0*glm::dot(qDir2, qminC2);
  c2 = (double)glm::dot(qminC2,qminC2) - (radius*radius);
  d2 = SolveQuadratic2(a2,b2,c2);
  if(d2 < 0 || isnan(d2) || d2< .001 || d2>dtRay.Gettmax() || d<.01){
    return false;
  }
  vec3 inPoint = GetVec3FromGLM(tRay.evaluate((double)d)); //intersection point in object space
  vec3 inPoint2 = GetVec3FromGLM(dtRay.evaluate((double)d2)); //intersection point in OS and tOS=tWS
  vec3 normal; //normal in object space
  sub(normal, inPoint, GetVec3FromGLM(m_pos)); //normal in object space
  normal.x=normal.x/radius; //normalize normal
  normal.y=normal.y/radius;
  normal.z=normal.z/radius;
  vec3 normals,inPoints,inPoints2;
  mult_dir(normals,GetMat4FromGLM(m_invT),normal); //(M^-1)^T * normal OS = normal in ws
  mult(inPoints, GetMat4FromGLM(m_transform), inPoint); // inPoint WS = M * intersection point in object space
  mult(inPoints2, GetMat4FromGLM(m_transform), inPoint2); //inPoint WS = M * intersection p in OS with real t
  normalize(normals); //normalize normal in WS
  *i = Intersection (GetGLMFromVec3(inPoints), m_material, d2, GetGLMFromVec3(normals), m_id); //inPoint WS, distance WS, normal WS
  return true;
}

bool Sphere::IntersectsP(Ray *q, Intersection *i){
  vec3 temp1, temp2, temp3;
  mult(temp1, GetMat4FromGLM(m_inverse), GetVec3FromGLM(q->Getq0())); ////M^-1 * r0 ;r0 of ray World Space to object space
  mult_dir(temp2,GetMat4FromGLM(m_inverse), GetVec3FromGLM(q->GetD())); //M^-1 * dir; dir of ray World Space to object space
  mult(temp3, GetMat4FromGLM(m_inverse),GetVec3FromGLM(q->Getp0()));//M^-1 * p0 ; p0 of ray World Space to OS
  normalize(temp2);//normalize dir in OS
  Ray tRay (GetGLMFromVec3(temp1),GetGLMFromVec3(temp2),
	    GetGLMFromVec3(temp3),q->Gettmax() );//make a ray in OS
  glm::dvec3 qDir = tRay.GetD(); //direction of ray in OS
  glm::dvec3 qminC = tRay.Getp0() - m_pos; //// p0 in OS - center of the sphere in OS
  double a, b, c , d;
  a = (double)glm::dot(qDir, qDir);
  b = (double)2.0*glm::dot(qDir, qminC);
  c = (double)glm::dot(qminC,qminC)-(radius*radius);
  d = SolveQuadratic(a,b,c);
  if(d < 0 || isnan(d) || d<.01 || d>tRay.Gettmax() ) {
    return false;
  }
  if(d==-2.0){//switch n1 n2
    
  }
  return true;
}

double Sphere::SolveQuadratic(double a, double b, double c){
	double discriminant  = b*b - 4.0*a*c;
		if(discriminant > 0.0) {
			discriminant = sqrt(discriminant);
			double root;
			root = (-1.0*b - discriminant)/(2.0*a);
			if(root <= 0.01){
				root = (-1.0*b + discriminant)/(2.0*a);
			}
			if (root <=0.01 || root > 100000.0 ){
				return -1;
			}
			return 1;
		}
	return -1; //discriminant < 0 complex roots
}

double Sphere::SolveQuadratic2(double a, double b, double c){
	double discriminant  = b*b - 4.0*a*c;
	if(discriminant < 0)
		return  discriminant; //complex roots
	discriminant = sqrt(discriminant);
	double root1, root2;
	double denom = 2.0*a;
	if (denom==0.0){
		return -1;
	}
	root1 = (-b - discriminant)/(2.0*a);
	root2 = (-b + discriminant)/(2.0*a);
	if(root1 <= 0.01 || root2 <= 0.01){ //one of the roots is negative switch n
		if (root1>=0.01){
			return root1; // root1 is positive and root2 is neg
		}
		else {
			return root2; // root2 is positive and root1 is neg
		}
	}
	else if (root1 > 0.01 && root2 > 0.01){// both roots are positive
		if (root1 < root2){
			return root1;
		}
		else if (root2 < root1){
			return root2;
		}
		else {// root2 == root1 tangent to sphere
			return root1;
		}
	}
	else{
		return -1;
	}
}

double Sphere::SolveQuadratic3 (double a, double b, double c){
	double discriminant  = b*b - 4.0*a*c;
	if(discriminant < 0)
		return  discriminant; //complex roots
	discriminant = sqrt(discriminant);
	double root1, root2;
	double denom = 2.0*a;
	if (denom==0.0){
		return -1;
	}
	root1 = (-b - discriminant)/(2.0*a);
	root2 = (-b + discriminant)/(2.0*a);
	if(root1 <= 0.0 || root2 <= 0.0){ //one of the roots is negative switch n
		return -2.0;
	}
	else if (root1 > 0.01 && root2 > 0.01){// both roots are positive
		if (root1 < root2){
			return root1;
		}
		else if (root2 < root1){
			return root2;
		}
		else {// root2 == root1 tangent to sphere
			return root1;
		}
	}
	else{
		return 0;
	}
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
