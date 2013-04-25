GCC_OPTIONS=-Wall -pedantic -I include 
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


red_triangle:
	g++ $@.cpp Common/InitShader.o $(OPTIONS) -o $@
	./red_triangle

clean:
	rm -f red_triangle
