P=prime
OBJECTS=
CFLAGS = -std=c11 -g -Wall -O3 -fopenmp $(shell pkg-config --cflags --libs cairo) -lm
LDLIBS=
CC=gcc
$(P): $(OBJECTS)
