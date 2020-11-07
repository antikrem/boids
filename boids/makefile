TAGS = -Wall -O2 -fopenmp

all:
	g++ -c $(TAGS) boid_settings.cpp
	g++ -c $(TAGS) helper.cpp
	g++ -c $(TAGS) point2.cpp
	g++ -c $(TAGS) boid.cpp
	g++ -c $(TAGS) main.cpp
	g++ $(TAGS) -o boid boid.o point2.o boid_settings.o helper.o main.o

clean:
	rm -f boid_settings.o helper.o main.o