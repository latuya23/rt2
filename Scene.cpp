#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include <fstream>
#include <getopt.h>
#include <stdio.h>
#include "Parser.h"
#include "Film.h"

int TESTS=1000;
int maxDepth=3;

std::ifstream inputfile;
std::ifstream tests;
std::ofstream file;
std::ifstream src;
std::ofstream dst;
const char* fileName = "currTest";
std::string fileNameNew = "currTest1";
bool avoidShadows = false;
bool avoidAllLightButKaKe = false;
bool noReflections = false;
bool noRefractions = false;

int main(int argc, char* argv[]) {
  if (argc == 1){
    tests.open("./namePaths");
  }
  else if (argc >= 3){ 
    int opt;
    int result = -1;
    while ((opt = getopt(argc,argv,"bcdef:")) != -1)
      switch(opt) {
       case 'f':
	 std::cout <<"reading " << fileName <<std::endl;
	 src.open(fileName, std::ios::binary);
	 dst.open(fileNameNew.c_str(), std::ios::binary);
	 dst << argv[2] << std::endl;
	 dst << src.rdbuf();
	 src.close();
	 dst.close();
	 //result = rename(fileName,"trash");
	 result = remove(fileName);
	 assert(result == 0);
	 result = rename(fileNameNew.c_str(),fileName);
	 assert(result ==0);
	break;
        case 'b':
	 std::cout <<"no reflections " <<std::endl;
	 noReflections = true;
	 break;
        case 'c':
	 std::cout <<"no refractions " <<std::endl;
	 noRefractions = true;
	 break;
	case 'd':
	 std::cout <<"no shadows " <<std::endl;
	 avoidShadows = true;
	 break;
        case 'e':
	 std::cout <<"no lights " << fileName <<std::endl;
	 avoidAllLightButKaKe = true;
	 break;
       case '?':
	 std::cout << "usage is: "<< std::endl;
	 std::cout << "-b : for no reflections" <<std::endl;
	 std::cout << "-c : for no refractions" <<std::endl;
	 std::cout << "-d : for no shadows" <<std::endl;
	 std::cout << "-e : for no lights" <<std::endl;
	 std::cout << "-f : for passing filename" <<std::endl;
	 break;
      default:
	std::cout<<std::endl;
	abort();
	break;
      }
    tests.open(fileName);
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
    assert(maxDepth>=1 && maxDepth <=5);
    myTracer.SetDebugNoShadows(avoidShadows);
    myTracer.SetDebugNoReflections(noReflections);
    myTracer.SetDebugNoRefractions(noRefractions);
    myTracer.SetDebugNoLightButKaKe(avoidAllLightButKaKe);
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
  }
  std::cout << "finished everything" << std::endl;
  return 0;
}
