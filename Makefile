SRC := src/*.cc
OUT := ./pjgen
OBJ := pjgen.o

all: compile link

compile:
	g++ -c $(SRC) -Isrc -std=c++20

link:
	g++ $(OBJ) -o $(OUT)

install:
	make
	sudo cp ./pjgen /usr/bin/
