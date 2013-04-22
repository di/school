GCC_OPTIONS=-Wall -pedantic -I include 
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


red_triangle:
	g++ $@.cpp Common/InitShader.o $(OPTIONS) -o $@
	g++ part2.cpp Common/InitShader.o $(OPTIONS) -o part2
	./red_triangle
	./part2

clean:
	rm -f red_triangle
