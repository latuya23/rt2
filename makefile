CC = g++
CFLAGS = -pipe  #-g -Wall 
//LLDLIBS =

all: raytracer
# ./nv/*.cpp
raytracer:
	$(CC) $(CFLAGS) *.cpp -o raytracer

clean:
	rm ./raytracer
