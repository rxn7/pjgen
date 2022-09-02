CC := g++
OBJ_DIR := obj
SRC_DIR := src src/templates
BIN_DIR := bin
OUT := $(BIN_DIR)/pjgen
INCFLAGS := -Isrc
CFLAGS := -std=c++20
SRC := $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: create_dirs $(OBJ) $(OUT)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

install:
	make
	sudo cp $(OUT) /usr/bin/
