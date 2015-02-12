#include "Film.h"


Film::Film() {
	m_image=0;
	SetFilm(1,1);
}

Film::Film(int x, int y) {
	m_image=0;
	SetFilm(x,y);
}

Film::~Film() {
	delete [] m_image;
}

void Film::SetFilm(int x, int y){
	m_width=x;
	m_height=y;
	if(m_image){
		delete[] m_image;
		m_image=0;
	}
	m_image = new Color[x*y];
}

void Film::InitializeFilm(){
	Color zero;
	for (int j=0; j<m_height;j++){
		for (int i=0; i<m_width;i++){
			m_image[m_width*j+i]=zero;
		}
	}
}
//Can be implemented just by a 2D array of Color
//(Later on, we can implement more complicated
//things such as multi-sample per pixel, or
//post processing, eg. tone mapping in this class)

void Film::Commit(Sample& sample, Color& color){
	//Will write the color to (sample.x, sample.y)
	//on the image
	int width = (int)sample.GetX();
	int height = (int)sample.GetY();
	if (width>=m_width || height>=m_height || width<0 || height<0){
		cout << "wrong sample \n" << endl;
	}
	else{
		m_image[m_width*height+width]=color;
	}
}

void Film::PrintColor(int x, int y){
	m_image[m_width*y+x].PrintColor();
}

void Film::PrintColors(){
	for (int j=0; j<m_height;j++){
		for (int i=0; i<m_width;i++){
			m_image[m_width*j+i].PrintColor();
		}
	}
}

void Film::WriteImage(){
	string file="RayTracedImage";
	WriteImage(file);
}

void Film::WriteImage(string writeTo){
	//output image to a file
	int r,g,b;
	Color temp;
	double max=255.0;
	writeTo.append(".ppm");
	ofstream outf(writeTo.c_str());
	if (!outf) {
		cerr<< "error opening file\n" << endl;
		exit(1);
	}
	cout<<"starting to write to image!"<<endl;
	outf<<"P3\n"<<m_width<<" "<<m_height<<"\n255";
	for (int i=0; i<m_height; i++) {
		outf<<"\n";
		for (int j=0; j<m_width;j++){
			temp=m_image[m_width*i+j];
			r=(int) max*temp.GetR();
			g=(int) max*temp.GetG();
			b=(int) max*temp.GetB();
			outf<<setw(3)<<r<<setw(4)<<g<<setw(4)<<b<<"   ";
		}
	}
}
