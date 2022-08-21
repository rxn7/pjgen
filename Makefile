OUT := pjgen
CC := g++
OBJ_DIR := obj
DIR_SRC := src src/templates
INC := -Isrc
CFLAGS := -std=c++20
SRC := $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: create_obj_dir $(OBJ) $(OUT)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

create_obj_dir:
	@mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJ) $(OUT)

install:
	make
	sudo cp $(OUT) /usr/bin/
