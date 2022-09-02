#include "CppTemplate.h"
#include "RunScript.h"

bool CppTemplate::_Generate(std::string &projectName) const {
	bool flagSimple = false;
	for(std::string_view flag : pjgen::flags) {
		if(flag == "simple") {
			flagSimple = true;
			break;
		}
	}

	std::string mainFileContent = 
R"(#include <iostream>

int main(int argc, const char **argv) {
	std::cout << "Hello, World!";
}
)";

	std::string mainFilePath;
	std::string makefilePath = "Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = "main.cpp";
		makefileContent = "all:\n\tg++ main.cpp -o &OUT&";
	} else {
		mainFilePath =  "src/main.cpp";
		makefileContent = 
R"(
CC := g++
OBJ_DIR := obj
SRC_DIR := src
BIN_DIR := bin
OUT := $(BIN_DIR)/&OUT&
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
	rm -rf $(OBJ_DIR) $(BIN_DIR))";

		if(!std::filesystem::create_directory("src")) {
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, mainFileContent);

	CreateRunScript(projectName);

	return true;
}
