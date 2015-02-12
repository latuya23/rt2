#!/bin/bash
#this script changes the file Scene.cpp to process only the given filename 
#call the script with the filename to process with raytracer
if [ $# -ne 1 ]; then
	echo -e "Usage: $0 filename"
else
	sed -e 's/TESTS[ ]*=[ ]*[0-9]*;/TESTS=1;/' -e 's/^[ \t]*outPut/\/\/outPut/' -e 's/^\/\/outPut\[0\].*/outPut[0]=\"'"$1"'\";/' Scene.cpp > $$
	mv $$ Scene.cpp
	g++ *.cpp ./nv/*.cpp -o raytracer	
	./raytracer
	sed -e 's/^\/\/outPut/outPut/' -e 's/TESTS[ ]*=[ ]*[0-9]*;/TESTS=26;/' Scene.cpp > $$
	mv $$ Scene.cpp
fi
