#ifndef FILM_H_
#define FILM_H_

#include "Color.h"
#include "Sample.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Film {
public:
	Film();
	Film(int x, int y);
	virtual ~Film();
	void SetFilm(int x, int y);
	void InitializeFilm();
	void Commit(Sample& sample, Color& color);
	void PrintColor(int x, int y);
	void PrintColors();
	void WriteImage();
	void WriteImage(string writeTo);

private:
	int m_width;
	int m_height;
	//Color ** m_image;
	Color * m_image;
};

#endif /* FILM_H_ */
