#include "Triangle.h"

Triangle::Triangle() {
	// TODO Auto-generated constructor stub
}

Triangle::Triangle(vec3 verts[3], vec3 norm, Material m)
{
	for(int i = 0; i < 3; i++){
		vertices[i] = verts[i];
		normals[i] = norm;
	}
	face_normal = norm;
	m_material = m;
}

Triangle::Triangle(vec3 verts[3], vec3 norms[3], Material m)
{
	for(int i = 0; i < 3; i++){
		vertices[i] = verts[i];
		normals[i] = norms[i];
	}
	m_material = m;
}

void Triangle::setFaceNormal(vec3 n){
	face_normal = n;
}

void Triangle::print(){
	cout<<"i am triangle!"<<endl;
	cout<<"vertices:"<<endl;
	cout<<"a:"<<endl;
	printVector(vertices[0]);
	cout<<"b:"<<endl;
	printVector(vertices[1]);
	cout<<"c:"<<endl;
	printVector(vertices[2]);
}
void Triangle::printVector(vec3 q0){
	cout<<"("<<q0.x<<","<<q0.y<<","<<q0.z<<")"<<endl;
}

bool Triangle::Intersects(Ray *r, Intersection *in){
	double t;
	double a=vertices[0].x -vertices[1].x;
	double b=vertices[0].y -vertices[1].y;
	double c=vertices[0].z -vertices[1].z;

	double d=vertices[0].x -vertices[2].x;
	double e=vertices[0].y -vertices[2].y;
	double f=vertices[0].z -vertices[2].z;

	double g=(double)r->GetD().x;
	double h=(double)r->GetD().y;
	double i=(double)r->GetD().z;

	double j=vertices[0].x - r->Getq0().x;
	double k=vertices[0].y - r->Getq0().y;
	double l=vertices[0].z - r->Getq0().z;

	double eihf = e*i-h*f;
	double gfdi = g*f-d*i;
	double dheg = d*h-e*g;

	double denom = (a*eihf + b*gfdi + c*dheg);

	double beta = (j*eihf + k*gfdi + l*dheg)/denom;

	if (beta <= 0.0 || beta >= 1.0)
	{
		return false;
	}
	double akjb = a*k - j*b;
	double jcal = j*c - a*l;
	double blkc = b*l - k*c;

	double gamma = (i*akjb + h*jcal + g*blkc)/denom;
	if (gamma <= 0.0 || beta + gamma >= 1.0)
	{
		return false;
	}

	t = -(f*akjb + e*jcal + d*blkc)/denom;
	if (t >= .01 && t <=r->Gettmax() && !isnan(t))
	{
		vec3 normal, v1v0,v2v0;
		sub(v1v0, vertices[1],vertices[0]);
		sub(v2v0, vertices[2],vertices[0]);
		cross(normal, v1v0,v2v0);
		normalize(normal);
		*in = Intersection (r->evaluate(t), m_material, t, face_normal);
		return true;
	}
	return false;
}

bool Triangle::IntersectsP(Ray *r, Intersection *in){
	double t;
	double a=vertices[0].x -vertices[1].x;
	double b=vertices[0].y -vertices[1].y;
	double c=vertices[0].z -vertices[1].z;

	double d=vertices[0].x -vertices[2].x;
	double e=vertices[0].y -vertices[2].y;
	double f=vertices[0].z -vertices[2].z;

	double g=(double)r->GetD().x;
	double h=(double)r->GetD().y;
	double i=(double)r->GetD().z;

	double j=vertices[0].x - r->Getq0().x;
	double k=vertices[0].y - r->Getq0().y;
	double l=vertices[0].z - r->Getq0().z;

	double eihf = e*i-h*f;
	double gfdi = g*f-d*i;
	double dheg = d*h-e*g;

	double denom = (a*eihf + b*gfdi + c*dheg);

	double beta = (j*eihf + k*gfdi + l*dheg)/denom;

	if (beta <= 0.0 || beta >= 1.0)
	{
		return false;
	}
	double akjb = a*k - j*b;
	double jcal = j*c - a*l;
	double blkc = b*l - k*c;

	double gamma = (i*akjb + h*jcal + g*blkc)/denom;
	if (gamma <= 0.0 || beta + gamma >= 1.0)
	{
		return false;
	}
	t = -(f*akjb + e*jcal + d*blkc)/denom;
	return (t >= .01 && t <= r->Gettmax() && !isnan(t));
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}
