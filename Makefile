CC = gcc

all: libTectonicPlate

ifeq ($(CC), clang)
libTectonicPlate:
	$(CC) -std=c11 -shared -o libTectonicPlate.so tectonic_plate.c	
endif


ifeq ($(CC), gcc)
libTectonicPlate:
	$(CC) -O3 -c -Wall -Werror -fpic -g tectonic_plate.c
	$(CC) -O3 -shared -o libTectonicPlate.so -g tectonic_plate.o
endif
