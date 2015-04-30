CC = g++
CFLAGS = -pipe -g -Wall
LDFLAGS = -g -Wall -pipe
TARGET = raytracer
CXXFILES = Scene.cpp Camera.cpp BRDF.cpp Color.cpp Light.cpp Ray.cpp Material.cpp Intersection.cpp Sample.cpp Parser.cpp Sampler.cpp Primitive.cpp Sphere.cpp Triangle.cpp PointLight.cpp RayTracer.cpp DirectionalLight.cpp Film.cpp AreaLight.cpp FaceList.cpp Model.cpp Box.cpp

OBJECTS = $(CXXFILES:.cpp=.o)

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
