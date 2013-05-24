GCC_OPTIONS=-Wall -pedantic -I include 
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


bezzy:
	g++ $@.cpp Common/InitShader.o $(OPTIONS) -o $@
	./bezzy

clean:
	rm -f bezzy
