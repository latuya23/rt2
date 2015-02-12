#include "RayTracer.h"

RayTracer::RayTracer() {
	cout<<"i have no maxDepth"<<endl;
}

RayTracer::RayTracer(int maxD){
	SetDepth(maxD);
}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}

void RayTracer::SetDepth(int maxD){
	m_Depth=maxD;
}

void RayTracer::traceRay(Ray *r, int depth, Color* tColor){
	if (depth>=m_Depth){
		return;
	}
	Intersection closest, temp;
	Material tempM;
	Color tempColor(0.0,0.0,0.0);
	Color tempKr(0.0,0.0,0.0);
	double tempKt=0.0;
	BRDF closestBRDF;
	Ray tempRay(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0));
	closest = Intersection(vec3(0,0,0), tempM, 100000.0, vec3(0,0,0));
	bool foundAny = false;
	for(unsigned int i = 0; i < myTriangles.size(); i++){
		if(myTriangles[i].Intersects(r, &temp)){
			foundAny = true;
			if(isCloser(r, temp, closest))
				closest = temp;
		}
	}
	for(unsigned int i = 0; i < mySpheres.size(); i++){
		if(mySpheres[i].Intersects(r, &temp)){
			foundAny = true;
			if(isCloser(r, temp, closest))
				closest = temp;
		}
	}
	if(!foundAny){
	    *tColor += tempColor;
		return;
	}
	// else there is an intersection
	closestBRDF = closest.GetMaterial().GetBRDF(); // get the BRDF from the closest intersection
	*tColor += closestBRDF.GetKa(); //add the Ka ambient of material
	*tColor += closestBRDF.GetKe(); //add the Ke emission of material
	// loop through all light sources
	// for an intersection
	// cast a shadow ray to all lights at the intersection
	// & determine if they are visible
	double shadow =1.0;
	for (unsigned int i=0; i< myLights.size(); i++){
		// cast a shadow ray to a light source at the intersection point & put it in tempRay
		myLights[i]->GenerateLightRay(closest.GetPosition(), &tempRay, closest.GetNormal());
		vec3 lPosorlDir=myLights[i]->GetPos(); //get the light position
		bool midir=myLights[i]->GetMIDir(); 

		// determine if the light is visible
		foundAny = false;
		temp = Intersection(vec3(0,0,0), tempM, 100000.0, vec3(0,0,0));

		for (unsigned int k = 0; k< myTriangles.size();k++){
			if ( myTriangles[k].IntersectsP(&tempRay, &temp)){
				foundAny=true;
				break;
			}
		}
		for(unsigned int k = 0; k < mySpheres.size(); k++){
			if (mySpheres[k].GetSphereId() == closest.GetId()){
				foundAny=false;
			}
			if(mySpheres[k].IntersectsP(&tempRay, &temp)){
				foundAny=true;
				break;
			}
		}
		if (foundAny){
			shadow=0.0;
		}
		//foundAny=false;
		// if we didn't find any
		//  do shading calculation for this
		// light source
		// Li(Kd max(li*n,0)+Ks(n*hi)^s) stars are dot products
		// Li = light color
		// Kd = diffuse
		// li = light direction
		// n = surface normal
		// Ks = specular
		// hi = half angle vector for the light
		// s = shininess
		//if(!foundAny){
			
			*tColor += shadow*Shading(myLights[i]->GetColor(),closestBRDF.GetKd(),closestBRDF.GetKs(),
					tempRay.GetD(),closest.GetNormal(),r->GetD(),closestBRDF.GetS()); 
		shadow=1.0;
	}

	// Handle mirror reflections
	tempKr = closestBRDF.GetKr();
	if ( (tempKr.GetR()>0.0) || (tempKr.GetG()>0.0) || (tempKr.GetB()>0.0) ) {
		Ray reflectRay = CreateReflectRay(r->GetD(), closest.GetNormal(), closest.GetPosition());
	    traceRay(&reflectRay, depth+1, &tempColor); // Make a recursive call to trace the reflected ray
	    tempColor = tempKr*tempColor;
	    *tColor += tempColor;
	}

	// Handle refractions
	tempKt = closestBRDF.GetKt();
	if (tempKt>0.0 && tempKt<=1.0){
		//cout<<tempKt<<endl;
		Ray refractRay = CreateRefractRay(r->GetD(),closest.GetNormal(),closest.GetPosition());

		traceRay(&refractRay, depth+1, &tempColor); //recursive call
		//tempColor =
		*tColor += tempColor;
	}


	return;
}

Ray RayTracer::CreateReflectRay(vec3 rDir, vec3 surfNormal, vec3 startP){
	vec3 tempV=rDir;
	scale(tempV,-1.0);
	vec3 refDir;
	reflect(refDir,surfNormal,tempV);
	vec3 tempVS=surfNormal;
	scale(tempVS,.01);
	vec3 startP2;
	add(startP2,tempVS,startP);
	Ray refRay(startP2,refDir,startP);
	return refRay;

}

Ray RayTracer::CreateRefractRay(vec3 rDir, vec3 surfNormal, vec3 startP){
	double n = 1.33;
	double cosI = dot(surfNormal, rDir);
	double sinT2 = n*n*(1.0-cosI*cosI);
	if (sinT2 > 1.0)
	{
		Ray refRay(vec3(0,0,0),vec3(0,0,0),vec3(0,0,0));
		return refRay;
	}
	vec3 tempDir, tempN, trDir;
	scale(tempDir, n);
	scale(tempN, (n+sqrt(1.0-sinT2)));
	sub(trDir, tempDir, tempN);
	normalize(trDir);

	vec3 tempVS=surfNormal;
	scale (tempVS, -.01);
	vec3 startP2;
	add(startP2,tempVS,startP);
	Ray refRay(startP2,trDir,startP);
	return refRay;
}


Color RayTracer::Shading(Color lColor,Color diffuse,Color specular, vec3 lightDir,
		vec3 normal, vec3 fromEye,double s){
	//  do shading calculation
	// Si Li(Kd max(li*n,0)+Ks max((n*hi)^s),0)) stars are dots
	// Si binary either shadow or not shadowed
	// Li = lColor; light color we have to attenuate
	// Kd = diffuse;  surface diffuse color
	// li = lightDir; light direction
	// n = normal; surface normal
	// Ks = specular; surface specular color
	// hi = half angle vector for the light
	// fromEye is the ray direction starting from eye
	// s=shininess
	vec3 tempV;
	long double temp1, temp2;
	scale(fromEye, -1.0);
	add(tempV,normalize(lightDir),normalize(fromEye)); // lightDir + fromEye
	normalize(tempV); //half angle = normalize(lightDir + fromEye)
	temp1=(long double)dot(normal, lightDir); //n*li

	if (temp1>1.1){
			temp1=1.0;
			cout<<"aaa1"<<endl;
			cout<<temp1<<endl;
			cout<<normal.x<<","<<normal.y<<","<<normal.z<<endl;
		}
	if (temp1<0.0 || isnan(temp1) || temp1< .0000001 || temp1>1000000.0){
		temp1=0.0;
	}
	temp2=(long double)dot(normal, tempV); //n*hi
	temp2= pow(temp2,s); //(n*hi)^s

	if (temp2>1.1){
		temp2=1.0;
		cout<<"aaa"<<endl;
	}
	if (temp2<0.0 || isnan(temp2) || temp2< .0000001 || temp2>1000000.0){
		temp2=0.0;
	}
	return lColor*((temp1*diffuse)+(temp2*specular));
}

bool RayTracer::isCloser(Ray *r, Intersection t1, Intersection t2){
	if(t1.GetT() < t2.GetT() && t2.GetT()>.01 && t1.GetT()>.01)
		return true;
	return false;
}

void RayTracer::addTriangle(Triangle tv){
	myTriangles.push_back(tv);
}

void RayTracer::addSphere(Sphere s){
	mySpheres.push_back(s);
}

void RayTracer::AddLight(Light* l){
	myLights.push_back(l);
}

void RayTracer::printSpheres(){
	for(unsigned int i = 0; i < mySpheres.size(); i++){
		mySpheres[i].print();
	}
}
void RayTracer::printTriangles(){
	for(unsigned int i = 0; i < myTriangles.size(); i++)
		myTriangles[i].print();
}

void RayTracer::PrintLight(){
	for (unsigned int i=0; i< myLights.size(); i++)
		myLights[i]->Print();
}
