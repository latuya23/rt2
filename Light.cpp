#include "Light.h"

Light::Light() {
	m_Light="undefined light";
}

Light::Light(std::string light, glm::dvec3 pos, Color c, glm::dvec3 dir, bool midirl){
	SetLight(pos,c,dir,midirl);
	m_Light=light;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::SetLight(glm::dvec3 pos, Color c, glm::dvec3 dir, bool midirl){
	m_position=pos;
	m_lightColor=c;
	m_dir= dir * -1.0; //reverse normalized dir of light
	m_idirl=midirl;
}

void Light::GenerateLightRay(glm::dvec3 inPoint, Ray *lRay, glm::dvec3 surfNormal){
	if(m_idirl){
		glm::dvec3 temp=surfNormal;
		temp = temp * .01;  // make ray closer to light ray = inpoint+.0001*m_dir
		glm::dvec3 temp2;
		temp2 = temp + inPoint; // add something in the direction of the light
		*lRay = Ray(temp2, m_dir, inPoint); //generate ray from inPoint towards reverse light direction
	}
	else{
		double dist;//tmax for ray
		glm::dvec3 temp;//m_dir = position of point light
		temp= m_position- inPoint; //direction of in to light
		dist = sqrt(temp.x*temp.x+temp.y*temp.y+temp.z*temp.z);
		temp = glm::normalize(temp); //normalized direction of ray to light
		glm::dvec3 temp2=surfNormal;
		temp2 = temp2* .01;
		glm::dvec3 temp3;
		temp3 = temp2 + inPoint; //add something in the direction of the light then shoot the ray
		*lRay = Ray(temp3,temp, inPoint, dist); //generate ray from temp3 towards the light with tmax dist
	}
}

bool Light::IsPointLight(){
	std::cout<<"error undefined light"<<std::endl;
	return false;
}
bool Light::IsDirLight(){
	std::cout<<"error undefined light"<<std::endl;
	return false;
}

void Light::Print(){
	std::cout<<"color:"<<std::endl;
	m_lightColor.PrintColor();
	std::cout<<"position:"<<std::endl;
	std::cout<<"x: "<<m_position.x<<" y: "<<m_position.y<<" z: "<<m_position.z<<std::endl;
	std::cout/*<<boolalpha*/<<"is directional light: "<<IsDirLight()<<std::endl;
	std::cout/*<<boolalpha*/<<"is point light: "<<IsPointLight()<<std::endl;
}
