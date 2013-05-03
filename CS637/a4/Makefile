GCC_OPTIONS=-Wall -pedantic -I include 
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


color_cube:
	g++ $@.cpp Common/InitShader.o $(OPTIONS) -o $@
	./color_cube

clean:
	rm -f color_cube
