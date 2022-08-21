#include "CppTemplate.h"

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
R"(OUT := &OUT&
CC := g++
OBJ_DIR := obj
DIR_SRC := src
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
