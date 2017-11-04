# Generic makefile

all: singing

clean:
	rm -f singing  *.o

LIBS = $(HOME)/$(LIB)/libfdr.a
INCLUDE = $(HOME)/include
CC = gcc

.SUFFIXES: .cpp .c .o .out .hist .jgr .jps .eps .nt .bib .tab .tex .dvi .fig .txt .ps .pdf .bin .od .odh .odd .ppm .gif

.cpp.o: 
	g++ -c -I$(INCLUDE) $*.cpp

.c.o: 
	g++ -c -I$(INCLUDE) $*.c


singing: Singing-Main.cpp Singing-Skeleton.cpp 
	g++ -o singing Singing-Main.cpp


