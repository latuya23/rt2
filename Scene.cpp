#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include <fstream>
#include "Parser.h"
#include "Film.h"

using namespace std;

const int TESTS=34;
int maxDepth=3;
static string outPut[TESTS];
static ifstream inputfile;

int main() {
outPut[0]="scene1.test";
outPut[1]="scene1-camera1.test";
outPut[2]="scene1-camera2.test";
outPut[3]="scene1-camera3.test";
outPut[4]="scene1-camera4.test";
outPut[5]="scene2-camera1.test";
outPut[6]="scene2-camera2.test";
outPut[7]="scene2-camera3.test";
outPut[8]="scene3.test";
outPut[9]="self.test";
outPut[10]="spheres.test";
outPut[11]="self1.test";
outPut[12]="spheres2.test";
outPut[13]="spheres3.test";
outPut[14]="scene3-2.test";
outPut[15]="self2.test";
outPut[16]="self3.test";
outPut[17]="self4.test";
outPut[18]="self2-1.test";
outPut[19]="self2-2.test";
outPut[20]="self4-2.test";
outPut[21]="self4-3.test";
outPut[22]="spheres4.test";
outPut[23]="self4-4.test";
outPut[24]="self4-5.test";
outPut[25]="self4-6.test";
outPut[26]="self2-3.test";
outPut[27]="self3-1.test";
outPut[28]="scene1-4.test";
outPut[29]="spheres4-1.test";
outPut[30]="spheres4-2.test";
outPut[31]="spheres4-3.test";
outPut[32]="spheres4-4.test";
outPut[33]="spheres4-5.test";

 	for (int names=0; names<TESTS; names++){
 		Film			 	myImage;
 		Camera			 	myCamera;
 		vector<Primitive> 	myPrimitives(1, Primitive());
 		vector<Triangle> 	myTriangles(1, Triangle());
 		Parser				myParser;
 		Sample				currSample(0,0);
 		Sampler				mySampler;
 		RayTracer			myTracer;
 		Ray					currRay(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0));
 		Color				currColor;


 	inputfile.open(outPut[names].c_str());
 	int *x,*y;
 	x =(int*) malloc(sizeof(int));
 	y =(int*) malloc(sizeof(int));
 	myParser.initialparse(inputfile, x, y);
 	myCamera.SetAspect(x, y);
 	myImage.SetFilm(*x,*y);
 	myImage.InitializeFilm();
 	mySampler.SetSamplerSize(*x, *y);
 	myParser.parsefile(inputfile, &myCamera, &myTracer, &maxDepth);
 	myTracer.SetDepth(maxDepth);
 	cout<<"maxDepth: "<<maxDepth<<endl;
 	assert(maxDepth>=2);
 	while(mySampler.GetSample(&currSample)){
			currColor.SetColor(0.0,0.0,0.0); // reset currColor to 0 every time
 	 		myCamera.GenerateRay(currSample,&currRay);
 	 		myTracer.traceRay(&currRay, 0, &currColor);
 	 		myImage.Commit(currSample, currColor);
 	 }
 	myImage.WriteImage(outPut[names]);
 	inputfile.close();
 	delete x;
 	delete y;
 	cout << "finished " << outPut[names] << endl;
 	}
 	cout << "finished everything" << endl;
 	return 0;
}
