#include "Sphere.h"

Sphere::Sphere() {
	// TODO Auto-generated constructor stub
}

Sphere::Sphere(glm::vec3 pos, double r, Material m, glm::mat4 inverse, glm::mat4 transform, glm::mat4 invT){
	m_pos = pos;
	radius = r;
	m_material = m;
	m_inverse = inverse;
	m_transform = transform;
	m_invT=invT;
	m_id= Sphere::next_sphere_id();
}

bool Sphere::Intersects(Ray *q, Intersection *i){
  glm::vec4 temp0,temp2,temp4;
	//mult(temp1, m_inverse, q->Getq0());// //M^-1 * r0 ;r0 of ray World Space to object space
	temp0 = m_inverse * glm::vec4(q->Getq0(),1);
	glm::vec3 temp1(temp0);
	/*c*///mult_dir(temp2, m_inverse, q->GetD()); //M^-1 * dir; dir of ray World Space to object space
	temp2 = m_inverse * glm::vec4(q->GetD(),0);
	glm::vec3 temp3(temp2);
	/*c*///mult(temp3, m_inverse, q->Getp0()); //M^-1 * p0 ; real p0 of ray World Space to OS
	temp4 = m_inverse * glm::vec4(q->Getp0(),1);
	glm::vec3 temp5(temp4);
	
	Ray dtRay(temp1,temp3,temp5,q->Gettmax()); //ray with unnormalized dir in OS
	temp2 = glm::normalize(temp2);//normalize dir in OS
	Ray tRay (temp1,temp3,temp5,q->Gettmax());//make a ray in OS
	glm::vec3 qDir = tRay.GetD(); //direction of ray in OS
	glm::vec3 qminC = tRay.Getp0() - m_pos;// // p0 in OS - center of the sphere in OS
	glm::vec3 qDir2 = dtRay.GetD(); //direction of ray in OS with unnormalized dir in OS
	glm::vec3 qminC2 = dtRay.Getp0() - m_pos;// // p0 in OS - center of the sphere in OS
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
	glm::vec3 inPoint = tRay.evaluate((double)d); //intersection point in object space
	glm::vec3 inPoint2 = dtRay.evaluate((double)d2); //intersection point in OS and tOS=tWS
	glm::vec3 normal; //normal in object space
	normal = inPoint - m_pos; //normal in object space
	normal.x=normal.x/radius; //normalize normal
	normal.y=normal.y/radius;
	normal.z=normal.z/radius;
	glm::vec3 normals,inPoints,inPoints2;
	/*c*///mult_dir(normals,m_invT,normal); //(M^-1)^T * normal OS = normal in ws
	/*c*///mult(inPoints, m_transform, inPoint); // inPoint WS = M * intersection point in object space
	/*c*///mult(inPoints2, m_transform, inPoint2); //inPoint WS = M * intersection p in OS with real t
	normals = glm::normalize(normals); //normalize normal in WS
	*i = Intersection (inPoints, m_material, d2, normals, m_id); //inPoint WS, distance WS, normal WS
	return true;
}

bool Sphere::IntersectsP(Ray *q, Intersection *i){
	glm::vec3 temp2, temp3;
	glm::vec4 temp0;
	temp0 = m_inverse * glm::vec4(q->Getq0(),0); ////M^-1 * r0 ;r0 of ray World Space to object space
	glm::vec3 temp1(temp0);
	/*c*///mult_dir(temp2, m_inverse, q->GetD()); //M^-1 * dir; dir of ray World Space to object space
	/*c*///mult(temp3, m_inverse,q->Getp0());//M^-1 * p0 ; p0 of ray World Space to OS
	temp2 = glm::normalize(temp2);//normalize dir in OS
	Ray tRay (temp1,temp2, temp3,q->Gettmax() );//make a ray in OS
	glm::vec3 qDir = tRay.GetD(); //direction of ray in OS
	glm::vec3 qminC = tRay.Getp0() - m_pos; //// p0 in OS - center of the sphere in OS
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
