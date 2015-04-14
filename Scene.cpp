#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include <fstream>
#include "Parser.h"
#include "Film.h"

int TESTS=35;
int maxDepth=3;

std::ifstream inputfile;
std::ifstream tests;

int main(int argc, char* argv[]) {
  if (argc == 1){
    tests.open("./namePaths");
  }
  else if (argc == 2){
    tests.open(argv[1]);
    TESTS = 1;
  }
  else {
    std::cout << "Usage: " << argv[0] << " filename" <<std::endl;
    return 0;
  }
  std::string outPut[TESTS];
  std::string line;
  int i = 0;
  while (tests.good() && i<TESTS){
    getline(tests, line);
    if (tests.eof()) {
      std::cout << "nothing left file " <<std::endl;
      break;
    }
    outPut[i] = line;
    i++;
  }
  for (int names=0; names<TESTS; names++){
    Film			myImage;// = NULL;
    Camera			myCamera;// = NULL;
    std::vector<Primitive> 	myPrimitives(1, Primitive());
    std::vector<Triangle> 	myTriangles(1, Triangle());
    Parser			myParser;// = NULL;
    Sample			currSample(0,0);
    Sampler			mySampler;// = NULL;
    RayTracer			myTracer;// = NULL;
    Ray			currRay(glm::dvec3(0,0,0), glm::dvec3(0,0,0), glm::dvec3(0,0,0));
    Color			currColor;
    outPut[names].insert(0,std::string("./tests/"));
    inputfile.open(outPut[names].c_str());
    int x,y;
    x =0;
    y =0;
    myParser.initialparse(inputfile, x, y);
    myCamera.SetAspect(x, y);
    myImage.SetFilm(x,y);
    myImage.InitializeFilm();
    mySampler.SetSamplerSize(x, y);
    myParser.parsefile(inputfile, &myCamera, &myTracer, &maxDepth);
    myTracer.SetDepth(maxDepth);
    std::cout<<"maxDepth: "<<maxDepth<<std::endl;
    assert(maxDepth>=1);
    while(mySampler.GetSample(&currSample)){
      currColor.SetColor(0.0,0.0,0.0); // reset currColor to 0 every time
      myCamera.GenerateRay(currSample,&currRay);
      myTracer.traceRay(&currRay, 0, &currColor);
      myImage.Commit(currSample, currColor);
    }
    std::string outFileName = "./results/" + outPut[names].substr(8);
    myImage.WriteImage(outFileName);
    //myImage.WriteImage(outPut[names]);
    inputfile.close();
    std::cout << "finished " << outPut[names] << std::endl;
    //delete myImage;
    //delete myCamera;
    myPrimitives.clear();
    myTriangles.clear();
    //delete myParser;
    //delete mySampler;
    //delete myTracer;
    //delete currColor;
  }
  std::cout << "finished everything" << std::endl;
  return 0;
}
