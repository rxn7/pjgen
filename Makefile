SRC := -c src/*.cpp -c src/templates/*.cpp
OUT := ./pjgen
OBJ := 	Main.o \
	Pjgen.o \
	ProjectTemplate.o \
	CTemplate.o \
	CppTemplate.o \
	WebTemplate.o \
	PythonTemplate.o

all: compile link clean

compile:
	g++ $(SRC) -Isrc -std=c++20

link:
	g++ $(OBJ) -o $(OUT)

clean:
	rm *.o

install:
	make
	sudo cp ./pjgen /usr/bin/
