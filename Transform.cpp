// Transform.cpp: implementation of the Transform class.
//
//////////////////////////////////////////////////////////////////////

#include "Transform.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Takes as input the current eye position, and the current up vector.
//up is always normalized to a lenght of 1.
//eye has a length indicating the distance from the viewer to the origin
void Transform::left(float degrees, vec3& eye, vec3& up) {

	nv_scalar rad = (degrees / 180) * 3.14159265;
	mat3 myMat = mat3();
	myMat.set_rot(rad, up);
	vec3 temp = vec3();
	eye = mult(temp, myMat, eye);
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 a = vec3();
	cross(a, eye, up);
	normalize(a);
	mat3 ident;
	nv_scalar rad = (degrees / 180) * 3.14159265;
	ident.a00 = cos(rad);
	ident.a01 = 0.0;
	ident.a02 = 0.0;
	ident.a10 = 0.0;
	ident.a11 = cos(rad);
	ident.a12 = 0.0;
	ident.a20 = 0.0;
	ident.a21 = 0.0;
	ident.a22 = cos(rad);

	nv_scalar c = 1.0 - cos(rad);
	mat3 tmp = mat3();
	tmp.a00 = c*a.x*a.x;
	tmp.a01 = c*a.x*a.y;
	tmp.a02 = c*a.x*a.z;
	tmp.a10 = c*a.x*a.y;
	tmp.a11 = c*a.y*a.y;
	tmp.a12 = c*a.z*a.y;
	tmp.a20 = c*a.x*a.z;
	tmp.a21 = c*a.z*a.y;
	tmp.a22 = c*a.z*a.z;

	nv_scalar sine = sin(rad);
	mat3 dual = mat3();
	dual.a00 = 0.0;
	dual.a01 = -1.0*a.z*sine;
	dual.a02 = a.y*sine;
	dual.a10 = a.z*sine;
	dual.a11 = 0;
	dual.a12 = -1.0*a.x*sine;
	dual.a20 = -1.0*a.y*sine;
	dual.a21 = a.x*sine;
	dual.a22 = 0;

	mat3 R = mat3();

	R = add(dual, tmp);
	R = add(R, ident);

	vec3 newEye = vec3();
	mult(newEye, R, eye);
	eye = newEye;

	vec3 newUp = vec3();
	mult(newUp, R, up);
	up = newUp;

}

mat4 Transform::lookAt(vec3 eye, vec3 up) {
	mat4 M;
	vec3 w = vec3();
	w.x = eye.x;
	w.y = eye.y;
	w.z = eye.z;
	normalize(w);
	vec3 norm_up = up;
	normalize(norm_up);
	vec3 u = vec3();
	u = cross(u, norm_up, w);
	vec3 v = vec3();
	v = cross(v, w, u);
	M = mat4();

	M.mat_array[0] = u.x;
	M.mat_array[4] = u.y;
	M.mat_array[8] = u.z;

	M.mat_array[1] = v.x;
	M.mat_array[5] = v.y;
	M.mat_array[9] = v.z;

	M.mat_array[2] = w.x;
	M.mat_array[6] = w.y;
	M.mat_array[10] = w.z;

	M.mat_array[12] = -1*dot(eye, u);
	M.mat_array[13] = -1*dot(eye, v);
	M.mat_array[14] = -1*dot(eye, w);


	M.mat_array[15] = 1.0;
    return M;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
