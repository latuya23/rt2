#include "Light.h"

Light::Light() {
	m_Light="undefined light";
}

Light::Light(string light, vec3 pos, Color c, vec3 dir, bool midirl){
	SetLight(pos,c,dir,midirl);
	m_Light=light;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::SetLight(vec3 pos, Color c, vec3 dir, bool midirl){
	m_position=pos;
	m_lightColor=c;
	m_dir=scale(dir,-1); //reverse normalized dir of light
	m_idirl=midirl;
}

void Light::GenerateLightRay(vec3 inPoint, Ray *lRay, vec3 surfNormal){
	if(m_idirl){
		vec3 temp=surfNormal;
		scale (temp, .01);  // make ray closer to light ray = inpoint+.0001*m_dir
		vec3 temp2;
		add (temp2, temp, inPoint); // add something in the direction of the light
		*lRay = Ray(temp2, m_dir, inPoint); //generate ray from inPoint towards reverse light direction
	}
	else{
		double dist;//tmax for ray
		vec3 temp;//m_dir = position of point light
		sub (temp, m_position, inPoint); //direction of in to light
		dist = sqrt(temp.x*temp.x+temp.y*temp.y+temp.z*temp.z);
		normalize(temp); //normalized direction of ray to light
		vec3 temp2=surfNormal;
		scale (temp2, .01);
		vec3 temp3;
		add (temp3, temp2, inPoint); //add something in the direction of the light then shoot the ray
		*lRay = Ray(temp3,temp, inPoint, dist); //generate ray from temp3 towards the light with tmax dist
	}
}

bool Light::IsPointLight(){
	cout<<"error undefined light"<<endl;
	return false;
}
bool Light::IsDirLight(){
	cout<<"error undefined light"<<endl;
	return false;
}

void Light::Print(){
	cout<<"color:"<<endl;
	m_lightColor.PrintColor();
	cout<<"position:"<<endl;
	cout<<"x: "<<m_position.x<<" y: "<<m_position.y<<" z: "<<m_position.z<<endl;
	cout<<boolalpha<<"is directional light: "<<IsDirLight()<<endl;
	cout<<boolalpha<<"is point light: "<<IsPointLight()<<endl;
}
