#include "CTemplate.h"
#include "RunScript.h"

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
R"(CC := gcc
OBJ_DIR := obj
SRC_DIR := src
BIN_DIR := bin
OUT := $(BIN_DIR)/&OUT&
INCFLAGS := -Isrc
SRC := $(wildcard $(addsuffix /*.c, $(SRC_DIR)))
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: create_dirs $(OBJ) $(OUT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm $(OBJ_DIR) $(BIN_DIR))";

		if(!std::filesystem::create_directory("src")) {
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, mainFileContent);

	CreateRunScript(projectName, !flagSimple);

	return true;
}
