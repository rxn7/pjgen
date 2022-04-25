OUT := ./pjgen

DIR_SRC += ./src
DIR_SRC += ./src/templates

CFLAGS := -std=c++20

SRC := $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
OBJ := $(patsubst %.cpp, %.o, $(SRC))

.PHONY: all
	
all: $(OBJ) $(OUT)

%.o: %.cpp
	g++ $(CFLAGS) -Isrc -c $< -o $@

$(OUT): $(OBJ)
	g++ $(CFLAGS) $(OBJ) -o $@

clean:
	rm -r $(OUT) $(OBJ)

install:
	make
	sudo cp ./pjgen /usr/bin/
