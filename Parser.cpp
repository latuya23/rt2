#include "Parser.h"
#include "nv/nv_math.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <iostream>

#define MAX_CHARS 1000
const float PI = 3.1415926535897932384;

struct Vertex {
	double pos[3];
};

struct VertexNormal {
	double pos[3];
	double normal[3];
};

void printMatrix(mat4 m){
	cout<<endl;
		for(int i = 0; i < 4; i++){
			cout<<endl;
			for(int j = 0; j <4; j++)
				cout<<m.mat_array[j*4+i]<<",";
		}
		cout<<endl;
}
static int tnumber;
int Sphere::next_id=0;
Vertex * vert=0;
VertexNormal * vertnorm=0;
int maxverts=0,maxvertnorms=0;
int curvert=0,curvertnorm=0;

int maxdepth=3;
int lightnum=0;

double attenuation[3] = {1.0, 0.0, 0.0} ;//set default attenuation
int parsed = 0 ;

void Parser::initialparse(ifstream &inputfile, int* sizex, int* sizey) {
	string line;
	char command[MAX_CHARS];
	while (inputfile.good()){
		getline (inputfile, line);
		if (inputfile.eof()) {cout << "Nothing in file \n"<<endl; exit(1);};
		if (line[0] == '#') continue; //comment lines
		int num = sscanf(line.c_str(), "%s", command);
		if (num != 1) continue; //Blank lines etc.
		else break;
	}

    /*****   SET IMAGE SIZE ******/ //The first line should be the size command setting the image size
    assert(!strcmp(command, "size")) ;
    int num = sscanf(line.c_str(), "%s %d %d", command, sizex, sizey);
    assert(num == 3) ;
    assert(!strcmp(command, "size")) ;
}

void Parser::parsefile(ifstream &inputfile, Camera *cam,  RayTracer *tracer, int* maxD){
	// this sets the default BRDF
	// whenever a primitive is created
	// this is used for its material
	// the defaults as in OpenGL are
	//ka ambient  = Color(0.2,0.2,0.2);
	//kd diffuse = Color(0.8,0.8,0.8);
	//ks specular = Color(0.0,0.0,0.0);
	//ke emission = Color(0.0,0.0,0.0);
	//kr reflection = Color(0.0,0.0,0.0);
	//s shininess = 0.0;

	BRDF tempBRDF;
	vector<mat4> transforms;
	mat4 identity, currMatrix, tempMat, helper,helper2,mvt;
	identityMatrix(identity);
	identityMatrix(currMatrix);
	identityMatrix(tempMat);
	identityMatrix(helper);
	identityMatrix(helper2);
	identityMatrix(mvt);
	vec3 tempVec;

	string line;
	char command[MAX_CHARS];
	while (!inputfile.eof()) {
		getline(inputfile, line);
		if (inputfile.eof()) break;
		if (line[0]=='#') continue; //comment lines
		int num = sscanf (line.c_str(), "%s", command);
		if (num != 1) continue; // Blank lines;

	// Now, we simply parse the file by looking at the first line for the various commands
    /**************        CAMERA LOCATION **********/
    if (!strcmp(command, "camera")) {
      double lookfrom[3], lookat[3], up[3], fov ;
      vec3 lookfrom0,lookat0,up0;

      int num = sscanf(line.c_str(), "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
		       command, lookfrom, lookfrom+1, lookfrom+2,
		       lookat, lookat+1, lookat+2, up, up+1, up+2, &fov) ;
      if (num != 11) {
    	  fprintf(stderr, "camera from[3] at[3] up[3] fov\n") ;
    	  exit(1) ;
      }
      assert(!strcmp(command,"camera")) ;

      // Set up modelview and projection matrices per camera parameters
	  lookfrom0.x=lookfrom[0];
	  lookfrom0.y=lookfrom[1];
	  lookfrom0.z=lookfrom[2];
	  lookat0.x=lookat[0];
	  lookat0.y=lookat[1];
	  lookat0.z=lookat[2];
	  up0.x=up[0];
	  up0.y=up[1];
	  up0.z=up[2];
	  cam->SetCamera(lookfrom0,lookat0,up0,fov);
    }

    /****************************************/
    /***********  GEOMETRY *******************/
    else if (!strcmp(command, "sphere")) {
	  double radius ; // Syntax is sphere x y z radius
	  double pos[3] ;
	  int num = sscanf(line.c_str(), "%s %lf %lf %lf %lf", command, pos, pos+1, pos+2, &radius);
	  if (num != 5) {
		fprintf(stderr, "sphere x y z radius\n") ;
		exit(1) ;
	  }
	 tempVec =  vec3((float)pos[0],(float)pos[1],(float)pos[2]);
	 invert(tempMat, currMatrix);
	 transpose(mvt, tempMat);
	 tracer->addSphere(Sphere(tempVec, radius, Material(tempBRDF), tempMat, currMatrix, mvt));// makes a sphere with material props from the tempBRDF
    }

	else if (!strcmp(command, "maxverts")) {
	  int num = sscanf(line.c_str(), "%s %d", command, &maxverts) ;
	  assert(num == 2) ; assert(maxverts > 0) ;
	  assert(!strcmp(command,"maxverts")) ;
	  assert(vert = new Vertex[maxverts]) ;
	}

	else if (!strcmp(command, "maxvertnorms")) {
	  int num = sscanf(line.c_str(), "%s %d", command, &maxvertnorms) ;
	  assert(num == 2) ; assert(maxvertnorms > 0) ;
	  assert(!strcmp(command,"maxvertnorms")) ;
	  assert(vertnorm = new VertexNormal[maxvertnorms]) ;
	}

	else if (!strcmp(command, "vertex")) {  // Add a vertex to the stack
	  assert(maxverts) ; assert(curvert < maxverts) ;
	  Vertex v ;
	  int num = sscanf(line.c_str(), "%s %lf %lf %lf", command, v.pos, v.pos+1, v.pos+2) ;
	  assert(num == 4) ; assert(!strcmp(command,"vertex")) ;
	  vert[curvert] = v ;
	  ++curvert ;
	}

	else if (!strcmp(command, "vertexnormal")) {  // Add a vertex to the stack with a normal
	  assert(maxvertnorms) ; assert(curvertnorm < maxvertnorms) ;
	  VertexNormal vn ;

	  int num = sscanf(line.c_str(), "%s %lf %lf %lf %lf %lf %lf",
		  command, vn.pos, vn.pos+1, vn.pos+2, 
		  vn.normal, vn.normal+1, vn.normal+2) ;

	  assert(num == 7) ; assert(!strcmp(command,"vertexnormal")) ;
	  vertnorm[curvertnorm] = vn ;
	  ++curvertnorm ;
	}

        else if (!strcmp(command, "tri")) { // Triangle from 3 vertices
	 int pts[3] ; 
	 int num = sscanf(line.c_str(), "%s %d %d %d", command, pts, pts+1, pts+2) ;
	 assert(num == 4) ; assert(!strcmp(command,"tri")) ;
	 int i,j ;
	 for (i = 0 ; i < 3 ; i++) {
	 assert(pts[i] >= 0 && pts[i] < maxverts) ;
	 }
	  double vertex[3][3] ;
	  double normal[3] ;
	  for (i = 0 ; i < 3 ; i++) 
	    for (j = 0 ; j < 3 ; j++)
	      vertex[i][j] = vert[pts[i]].pos[j] ;
	  
	  
	  // Calculate the face normal 
	  double vec1[3], vec2[3], vect3[3] ;
	  for (i = 0 ; i < 3 ; i++) {
		  vec1[i] = vertex[1][i] - vertex[0][i] ;
		  vec2[i] = vertex[2][i] - vertex[0][i] ;
	  }
	  vect3[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1] ;
	  vect3[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2] ;
	  vect3[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0] ;

	  double norm = 0 ;
	  for (i = 0 ; i < 3 ; i++) norm += vect3[i] * vect3[i] ;
	  norm = sqrt(norm) ;
      if (norm == 0) {normal[0] = 0 ; normal[1] = 0 ; normal[2] = 1.0 ;}
	  else {
		for (i = 0 ; i < 3 ; i++) normal[i] = vect3[i] / norm ;
	  }

      //starts
      vec3 verts[3], temps[3], tempnormie;
      for(i = 0; i < 3; i++){
    	  verts[i] = vec3((float)vertex[i][0], (float)vertex[i][1],(float)vertex[i][2]);
    	  mult(temps[i], currMatrix, verts[i]);
      }
      vec3 normie((float)normal[0], (float)normal[1], (float)normal[2]);
      invert(tempMat, currMatrix);
      transpose(tempMat);
      mult(tempnormie,tempMat,normie);
      normalize(tempnormie);
      Triangle t(temps, tempnormie, Material(tempBRDF));// makes a triangle with material props from the tempBRDF
      tracer->addTriangle(t);
      }

        else if (!strcmp(command, "trinormal")) {
	  int pts[3] ;
	  int num = sscanf(line.c_str(), "%s %d %d %d", command, pts, pts+1, pts+2) ;
	  assert(num == 4) ; assert(!strcmp(command,"trinormal")) ;
	  int i;
	  for (i = 0 ; i < 3 ; i++) {
	    assert(pts[i] >= 0 && pts[i] < maxvertnorms) ;
	  }
	  printf("trinormal\n");
      vec3 verts[3];
      vec3 normie[3];
      for(int i = 0; i < 3; i++){
    		  verts[i] = vec3((float)vertnorm[pts[i]].pos[0], (float)vertnorm[pts[i]].pos[1],(float)vertnorm[pts[i]].pos[2]);
    		  normie[i] = vec3((float)vertnorm[pts[i]].normal[0], (float)vertnorm[pts[i]].normal[1], (float)vertnorm[pts[i]].normal[2]);
      }

	  double normal[3] ;
	  double vec1[3], vec2[3], vect3[3] ;
	  for (i = 0 ; i < 3 ; i++) {
		  vec1[i] = vertnorm[1].pos[i] - vertnorm[0].pos[i] ;
		  vec2[i] = vertnorm[2].pos[i] - vertnorm[0].pos[i] ;
	  }
	  vect3[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1] ;
	  vect3[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2] ;
	  vect3[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0] ;

	  double norm = 0 ;
	  for (i = 0 ; i < 3 ; i++) norm += vect3[i] * vect3[i] ;
	  norm = sqrt(norm) ;
      if (norm == 0) {normal[0] = 0 ; normal[1] = 0 ; normal[2] = 1.0 ; }
	  else {
		for (i = 0 ; i < 3 ; i++) normal[i] = vect3[i] / norm ;
	  }
      Triangle t(verts, normie, Material(tempBRDF));// makes a triangle with material props from the tempBRDF
      t.setFaceNormal(vec3 ((float)normal[0], (float)normal[1], (float)normal[2]));
      tracer->addTriangle(t);
	}

    /******************************************/
    /**************** TRANSFORMATIONS *********/
	else if (!strcmp(command, "translate")) {
	  double x,y,z ; // Translate by x y z as in standard OpenGL
	  int num = sscanf(line.c_str(), "%s %lf %lf %lf",command, &x, &y, &z) ;
	  if (num != 4) {
		fprintf(stderr, "translate x y z\n") ;
		exit(1) ;
	  }
	    currMatrix.a03 += (float)x;
	  	currMatrix.a13 += (float)y;
	  	currMatrix.a23 += (float)z;
	}

	else if (!strcmp(command, "rotate")) {
	  double ang, x,y,z ; // Rotate by an angle about axis x y z as in standard OpenGL
	  int num = sscanf(line.c_str(), "%s %lf %lf %lf %lf",command, &x, &y, &z, &ang) ;
	  if (num != 5) {
		fprintf(stderr, "rotate angle x y z\n") ;
		exit(1) ;
	  }
	  vec3 tempVec =vec3 ((float)x,(float)y,(float)z);
	  normalize(tempVec);
	  identityMatrix(helper);
	  helper.set_rot((float)ang*(float)PI/(float)180.0,tempVec);
	  helper2=currMatrix;
	  mult(currMatrix, helper2, helper);
	}

	else if (!strcmp(command, "rotatex")) {
		  double ang; // Rotate by an angle about x axis as in standard OpenGL
		  int num = sscanf(line.c_str(), "%s %lf ",command, &ang) ;
		  if (num != 2) {
			fprintf(stderr, "rotatex angle \n") ;
			exit(1) ;
		  }
		  identityMatrix(helper);
		  helper.set_rotx((float)ang*(float)PI/(float)180.0);
		  helper2=currMatrix;
		  mult(currMatrix, helper2, helper);
		}

	else if (!strcmp(command, "rotatey")) {
			  double ang; // Rotate by an angle about x axis as in standard OpenGL
			  int num = sscanf(line.c_str(), "%s %lf ",command, &ang) ;
			  if (num != 2) {
				fprintf(stderr, "rotatey angle \n") ;
				exit(1) ;
			  }
			  identityMatrix(helper);
			  helper.set_roty((float)ang*(float)PI/(float)180.0);
			  helper2=currMatrix;
			  mult(currMatrix,helper2,helper);
			}

	else if (!strcmp(command, "rotatez")) {
			  double ang; // Rotate by an angle about x axis as in standard OpenGL
			  int num = sscanf(line.c_str(), "%s %lf ",command, &ang) ;
			  if (num != 2) {
				fprintf(stderr, "rotatez angle \n") ;
				exit(1) ;
			  }
			  identityMatrix(helper);
			  helper.set_rotz((float)ang*(float)PI/(float)180.0);
			  helper2=currMatrix;
			  mult(currMatrix,helper2,helper);
			}

	else if (!strcmp(command, "scale")) {
	  double x,y,z ; // Scale by x y z as in standard OpenGL
	  int num = sscanf(line.c_str(), "%s %lf %lf %lf",command, &x, &y, &z) ;
	  if (num != 4) {
		fprintf(stderr, "scale x y z\n") ;
		exit(1) ;
	  }
	  identityMatrix(helper);
	  helper.a00=(float)x;
	  helper.a11=(float)y;
	  helper.a22=(float)z;
	  helper2=currMatrix;
	  mult(currMatrix,helper2,helper);
	}

	else if (!strcmp(command, "pushTransform")) {
	 transforms.push_back(currMatrix); // Push the current matrix on the stack as in OpenGL
	  }

	else if (!strcmp(command, "popTransform")) {
	  currMatrix = transforms.back(); // Pop the current matrix as in OpenGL
	  transforms.pop_back();
	}

        else if (!strcmp(command, "maxdepth")) {
	  int num = sscanf(line.c_str(), "%s %d", command, &maxdepth) ;
	  assert(num == 2) ;
	  assert(!strcmp(command, "maxdepth")) ;
	  *maxD=maxdepth;
	  cout<<" maxdepth: "<<*maxD<<endl;
	}

       else if (!strcmp(command, "output")) {
	   char out[300] ;
	   int num = sscanf(line.c_str(), "%s %s", command, out) ;
	   assert(num == 2) ;
	   assert(!strcmp(command, "output")) ;
	   //output->assign(out);
	   //cout<<*output<<endl;
      }

    /*************************************************/
    /***************  LIGHTS *******************/
     else if (!strcmp(command, "directional")) {
	 float direction[4], color[4] ; color[3] = 1.0 ; direction[3] = 0.0 ;
	 int num = sscanf(line.c_str(), "%s %f %f %f %f %f %f", command, direction, direction+1, direction+2, color, color+1, color+2) ;
	 assert(num == 7) ;
	 
	vec3 temp(direction[0],direction[1],direction[2]);
	vec3 temp2=temp;
	normalize(temp2);
	Color tempC(color[0],color[1],color[2]);
	Light* tempLight = new DirectionalLight(temp,tempC,temp2);
	tempLight->m_idirl = true;
	tracer->AddLight(tempLight);
   }

      else if (!strcmp(command, "point")) {
	 float direction[4], color[4] ; color[3] = 1.0 ; direction[3] = 1.0 ;
	 int num = sscanf(line.c_str(), "%s %f %f %f %f %f %f", command, direction, direction+1, direction+2, color, color+1, color+2) ;
	 assert(num == 7) ;
	 
	 vec3 temp(direction[0],direction[1],direction[2]);
	 Color tempC((double)color[0],(double)color[1],(double)color[2]);
	 Light* tempLight = new PointLight(temp,tempC,temp,attenuation[0],attenuation[1],attenuation[2]);
	tempLight->m_idirl = false;
	 tracer->AddLight(tempLight);
	 }

     else if (!strcmp(command, "attenuation")) {
       int num = sscanf(line.c_str(), "%s %lf %lf %lf", command, attenuation, attenuation + 1, attenuation +2) ;
       assert(num == 4) ;
       assert(!strcmp(command, "attenuation")) ;

       // this changes the attenuation and
       // whenever we set a point light,
       // since attenuation is a global variable,
       // these are the values used to set
       // its attenuation
     }

     else if (!strcmp(command, "ambient")) {
       float ambient[4] ; ambient[3] = 1.0 ;
       int num = sscanf(line.c_str(), "%s %f %f %f", command, ambient, ambient+1, ambient+2) ;
       assert(num == 4) ;
       assert(!strcmp(command, "ambient")) ;

       // changes the ka in the tempBRDF used to set primitives' material
       tempBRDF.SetKa(Color((double)ambient[0],(double)ambient[1],(double)ambient[2]));
     }

    /*******************************************************/
    /****************** MATERIALS ************************/
     else if (!strcmp(command, "diffuse")) {
       float diffuse[4] ; diffuse[3] = 1.0 ;
       int num = sscanf(line.c_str(), "%s %f %f %f", command, diffuse, diffuse+1, diffuse+2) ;
       assert(num == 4) ; assert (!strcmp(command, "diffuse")) ;

       // changes the kd in the tempBRDF used to set primitives' material
       tempBRDF.SetKd(Color((double)diffuse[0],(double)diffuse[1],(double)diffuse[2]));
     }

     else if (!strcmp(command, "specular")) {
       float specular[4] ; specular[3] = 1.0 ;
       int num = sscanf(line.c_str(), "%s %f %f %f", command, specular, specular+1, specular+2) ;
       assert(num == 4) ; assert (!strcmp(command, "specular")) ;
       
       // changes the Ks in the tempBRDF used to set primitives' material
       tempBRDF.SetKs(Color((double)specular[0],(double)specular[1],(double)specular[2]));
     }

     else if (!strcmp(command, "shininess")) {
       float shininess ;
       int num = sscanf(line.c_str(), "%s %f", command, &shininess) ;
       assert(num == 2) ; assert (!strcmp(command, "shininess")) ;
       
       // changes the s (shininess) in the tempBRDF used to set primitives' material
       tempBRDF.SetS((double)shininess);
     }

     else if (!strcmp(command, "emission")) {
       float emission[4] ; emission[3] = 1.0 ;
       int num = sscanf(line.c_str(), "%s %f %f %f", command, emission, emission+1, emission+2) ;
       assert(num == 4) ; assert (!strcmp(command, "emission")) ;
      
       // changes the Ke in the tempBRDF used to set primitives' material
       tempBRDF.SetKe(Color((double)emission[0],(double)emission[1],(double)emission[2]));
     }

     else if (!strcmp(command, "reflection")) {
       float reflection[3];
       int num = sscanf(line.c_str(), "%s %f %f %f", command, reflection, reflection+1, reflection+2) ;
       assert(num == 4) ; assert (!strcmp(command, "reflection")) ;

       // changes the Kr in the tempBRDF used to set primitives' material
       tempBRDF.SetKr(Color((double)reflection[0],(double)reflection[1],(double)reflection[2]));
     }

     else if (!strcmp(command, "refraction")) {
       double refraction;
       int num = sscanf(line.c_str(), "%s %lf", command, &refraction) ;
       assert(num == 2) ; assert (!strcmp(command, "refraction")) ;

       // changes the Kt in the tempBRDF used to set primitives' material
       tempBRDF.SetKt((double)refraction);
     }


    /*****************************************************/
    else {
      fprintf(stderr, "Unimplemented command: %s\n", command) ;
      exit(1) ;
    }
  }
   vert=0;
   vertnorm=0;
   maxverts=0;
   maxvertnorms=0;
   curvert=0;
   curvertnorm=0;
   maxdepth=3;
   lightnum=0;
   parsed = 0 ;
   tnumber++;
   cout << "parsing ended successfully " << tnumber << endl;
}
