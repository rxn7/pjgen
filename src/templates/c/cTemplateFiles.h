#pragma once

#define C_TEMPLATE_MAIN_FILE_CONTENT \
    "#include <stdio.h>\n" \
    "int main(int argc, const char **argv) {\n" \
    "    printf(\"Hello, World!\\n\");\n" \
    "}"

#define C_TEMPLATE_MAKEFILE_SIMPLE_CONTENT \
    "all:\n\tgcc main.c -o &OUT&"

#define C_TEMPLATE_MAKEFILE_CONTENT \
    "CC := gcc\n" \
    "OBJ_DIR := obj\n" \
    "SRC_DIR := src\n" \
    "BIN_DIR := bin\n" \
    "OUT := $(BIN_DIR)/&OUT&\n" \
    "INCFLAGS := -Isrc\n" \
    "SRC := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp)\n" \
    "OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))\n" \
"\n" \
    "all: create_dirs $(OBJ) $(OUT)\n" \
"\n" \
    "$(OBJ_DIR)/%.o: %.c\n" \
    "\t@mkdir -p $(@D)\n" \
    "\t$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@\n" \
"\n" \
    "$(OUT): $(OBJ)\n" \
    "\t@mkdir -p $(@D)\n" \
    "\t$(CC) $(OBJ) $(LDFLAGS) -o $@\n" \
"\n" \
    "create_dirs:\n" \
    "\t@mkdir -p $(OBJ_DIR) $(BIN_DIR)\n" \
"\n" \
    "clean:\n" \
    "\trm -rf $(OBJ_DIR) $(BIN_DIR)"
