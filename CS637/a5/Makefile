GCC_OPTIONS=-Wall -pedantic -I include 
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


teapot:
	g++ $@.cpp Common/InitShader.o $(OPTIONS) -o $@
	./teapot

clean:
	rm -f teapot
