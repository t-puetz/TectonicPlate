CC = gcc

all: triangle

triangle:
	sudo cp -v ../libTectonicPlate.so /usr/lib/
	$(CC) -O3 -lglfw -lvulkan -lTectonicPlate -g triangle.c -o triangle

