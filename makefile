CC=g++
CFLAGS=-Wall

all: raytracer

raytracer:
	$(CC) $(CFLAGS) *.cpp ./nv/*.cpp -o raytracer

clean:
	rm ./raytracer
