#pragma once

#define CPP_TEMPLATE_MAIN_FILE_CONTENT \
    "#include <iostream>\n" \
    "int main(int argc, const char **argv) {\n" \
    "\tstd::cout << \"Hello, World!\";\n" \
    "}"

#define CPP_TEMPLATE_MAKEFILE_SIMPLE_CONTENT \
    "all:\n" \
    "\tg++ main.cpp -o &OUT&"

#define CPP_TEMPLATE_MAKEFILE_CONTENT \
    "CC := g++\n" \
    "OBJ_DIR := obj\n" \
    "SRC_DIR := src\n" \
    "BIN_DIR := bin\n" \
    "OUT := $(BIN_DIR)/&OUT&\n" \
    "INCFLAGS := -Isrc\n" \
    "CFLAGS := -std=c++20\n" \
    "SRC := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp)\n" \
    "OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))\n" \
"\n" \
    "all: create_dirs $(OBJ) $(OUT)\n" \
"\n" \
    "$(OBJ_DIR)/%.o: %.cpp\n" \
    "\t@mkdir -p $(@D)\n" \
    "\t$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@\n" \
"\n" \
    "$(OUT): $(OBJ)\n" \
    "\t@mkdir -p $(@D)\n" \
    "\t$(CC) $(LDFLAGS) $(OBJ) -o $@\n" \
"\n" \
    "create_dirs:\n" \
    "\t@mkdir -p $(OBJ_DIR) $(BIN_DIR)\n" \
"\n" \
    "clean:\n" \
    "\trm -rf $(OBJ_DIR) $(BIN_DIR)"