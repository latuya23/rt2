#include "RayTracer.h"

RayTracer::RayTracer() {
  std::cout<<"i have no maxDepth"<<std::endl;
}

RayTracer::RayTracer(int maxD){
	SetDepth(maxD);
	avoidShadows = false;
	avoidAllLightButKaKe = false;
	avoidRefractions = false;
	avoidReflections = false;
}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
  for (unsigned int i = 0; i< myPrims.size(); i++){
    delete myPrims[i];
  }
}

void RayTracer::SetDebugNoShadows(bool noShadows){
  avoidShadows = noShadows;
  if (noShadows){
    std::cout<<"debugging no shadows"<<std::endl;
  }
}

void RayTracer::SetDebugNoReflections(bool noRefl){
  avoidReflections = noRefl;
  if (noRefl){
    std::cout<<"debugging no reflections"<<std::endl;
  }
}

void RayTracer::SetDebugNoRefractions(bool noRefr){
  avoidRefractions = noRefr;
  if (noRefr){
    std::cout<<"debugging no refractions"<<std::endl;
  }
}

void RayTracer::SetDebugNoLightButKaKe(bool kaKeOnly){
  avoidAllLightButKaKe = kaKeOnly;
  if (kaKeOnly){
    std::cout<<"debugging no light only ambient and emission"<<std::endl;
  }
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
  Ray tempRay(glm::dvec3(0), glm::dvec3(0), glm::dvec3(0));
  std::vector<Ray*> tempRays;
  closest = Intersection(glm::dvec3(0), tempM, 100000.0, glm::dvec3(0));
  bool foundAny = false;
  for (unsigned int i = 0; i < myPrims.size(); i++){
    if (myPrims[i]->Intersects(r,&temp)){
      foundAny = true;
      if(isCloser(r,temp,closest)){
	closest = temp;
      }
    }
  }
  if(!foundAny){
    *tColor += tempColor;
    return;
  }
  // else there is an intersection
  closestBRDF = closest.GetMaterial().GetBRDF(); // get the BRDF from the closest intersection
  if (depth == 0){
    *tColor += closestBRDF.GetKa(); //add the Ka ambient of material
    *tColor += closestBRDF.GetKe(); //add the Ke emission of material
  }
  // loop through all light sources
  // for an intersection
  // cast a shadow ray to all lights at the intersection
  // & determine if they are visible
  double shadow =0.0;
  for (unsigned int i=0; i< myLights.size(); i++){
    if (avoidAllLightButKaKe){
      continue;
    }
    // cast a shadow ray to a light source at the intersection point & put it in tempRay
    myLights[i]->GenerateLightRays(closest.GetPosition(), &tempRays, closest.GetNormal());
    float invSamples = 1.0/tempRays.size();
    for(std::vector<Ray*>::iterator it=tempRays.begin();
	it!=tempRays.end(); ++it) {
      // determine if the light is visible
      foundAny = check4Intersection(*it);
      if (avoidShadows){
	foundAny = false;
      }
      if (!foundAny){
	shadow=invSamples;
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
	*tColor += shadow*
	  Shading(myLights[i]->GetColor(),closestBRDF.GetKd(),
		  closestBRDF.GetKs(),(*it)->GetD(),
		  closest.GetNormal(),r->GetD(),
		  closestBRDF.GetS()); 
      }
    }
    //shadow = 1 - (shadow / tempRays.size());
    shadow=0.0;
    tempRays.clear();
  }
  // Handle mirror reflections
  tempKr = closestBRDF.GetKr();
  if ( ((tempKr.GetR()>0.0) || (tempKr.GetG()>0.0) ||
       (tempKr.GetB()>0.0)) && avoidReflections == false ) {
    Ray reflectRay = CreateReflectRay(r->GetD(), closest.GetNormal(), closest.GetPosition());
    traceRay(&reflectRay, depth+1, &tempColor); // Make a recursive call to trace the reflected ray
    tempColor = tempKr*tempColor;
    *tColor += tempColor;
  }
  
  // Handle refractions
  tempKt = closestBRDF.GetKt();
  if (tempKt>0.0 && avoidRefractions == false){
    //std::cout<<tempKt<<std::endl;
    Ray refractRay = CreateRefractRay(r->GetD(),closest.GetNormal(),
				      closest.GetPosition(),depth);
    
    traceRay(&refractRay, depth+1, &tempColor); //recursive call
    //tempColor *= 
    *tColor += tempColor;
  }
  return;
}

bool RayTracer::check4Intersection(Ray* ray){
  for(unsigned int i = 0; i<myPrims.size();i++){
    if (myPrims[i]->IntersectsP(ray)){
      return true;
    }
  }
  return false;
}

Ray RayTracer::CreateReflectRay(glm::dvec3 rDir, glm::dvec3 surfNormal, glm::dvec3 startP){
  glm::dvec3 refDir = glm::reflect(rDir,surfNormal);
  Ray refRay(startP+(surfNormal*.01),refDir,startP);
  return refRay; 
}

Ray RayTracer::CreateRefractRay(glm::dvec3 rDir, glm::dvec3 surfNormal,
				glm::dvec3 startP, int depth){
  double n1Overn2 = 1.0;
  
  if (depth % 2 == 1){
    n1Overn2 =1.33;
    surfNormal = -surfNormal; 
  }
  else{
    n1Overn2 = .7518797;
  }
  glm::dvec3 refDir = glm::normalize(glm::refract(rDir,surfNormal,n1Overn2));
  Ray refRay(startP,refDir,startP);
  return refRay;
}


Color RayTracer::Shading(Color lColor,Color diffuse,Color specular, glm::dvec3 lightDir,
			 glm::dvec3 normal, glm::dvec3 fromEye,double s){
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
  glm::dvec3 tempV;
  double temp1, temp2;
  fromEye = fromEye * -1.0;
  tempV = lightDir + fromEye; // lightDir + fromEye
  tempV = glm::normalize(tempV); //half angle = normalize(lightDir + fromEye)
  temp1= glm::dot(normal, lightDir); //n*li
  
  if (temp1>1.1){
    temp1=1.0;
    std::cout<<"aaa1"<<std::endl;
    std::cout<<temp1<<std::endl;
    std::cout<<normal.x<<","<<normal.y<<","<<normal.z<<std::endl;
  }
  if (temp1<0.0 || isnan(temp1) || temp1< .0000001 || temp1>1000000.0){
    temp1=0.0;
  }
  temp2=glm::dot(normal, tempV); //n*hi
  temp2= pow(temp2,s); //(n*hi)^s
  
  if (temp2>1.1){
    temp2=1.0;
    std::cout<<"aaa"<<std::endl; 
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

void RayTracer::AddPrimitive(Primitive* prim){
  myPrims.push_back(prim);
}

void RayTracer::AddLight(Light* l){
  myLights.push_back(l);
}

void RayTracer::PrintPrims(){
  for (unsigned int i = 0; i < myPrims.size(); i++){
    myPrims[i]->Print();
  }
 }

void RayTracer::PrintLight(){
  for (unsigned int i=0; i< myLights.size(); i++)
    myLights[i]->Print();
}
