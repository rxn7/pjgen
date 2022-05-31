#include "CTemplate.h"

bool CTemplate::_Generate(std::string &projectName) const {
	bool flagSimple = false;
	for(std::string_view flag : pjgen::flags) {
		if(flag == "simple") {
			flagSimple = true;
			break;
		}
	}

	std::string mainFileContent = 
R"(#include <stdio.h>

int main(int argc, const char **argv) {
	printf("Hello, World!\n");
})";

	std::string mainFilePath;
	std::string makefilePath = "Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = "main.c";
		makefileContent = "all:\n\tgcc main.c -o &OUT&";
	} else {
		mainFilePath = "src/main.c";
		makefileContent = 
R"(OUT := &OUT&
CC := gcc
OBJ_DIR := obj
DIR_SRC := src
INC := -Isrc
SRC := $(wildcard $(addsuffix /*.c, $(DIR_SRC)))
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: create_obj_dir $(OBJ) $(OUT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LIBS) $(OBJ) -o $@

create_obj_dir:
	@mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJ) $(OUT))";

		if(!std::filesystem::create_directory("src")) {
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, mainFileContent);

	return true;
}
