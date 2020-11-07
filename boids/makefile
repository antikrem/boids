TAGS = -Wall -O2 -fopenmp

all:
	g++ -c $(TAGS) boid_settings.cpp
	g++ -c $(TAGS) helper.cpp
	g++ -c $(TAGS) main.cpp
	g++ -o $(TAGS) boid boid_settings.o helper.o main.o

clean:
	rm -f boid_settings.o helper.o main.o