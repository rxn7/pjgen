#include "CppTemplate.h"

constexpr std::string_view CppTemplate::GetName() const {
	return "C++";
}

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
	std::string makefilePath = pjgen::rootDirPath + "/Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = pjgen::rootDirPath + "/main.cpp";
		makefileContent = "all:\n\tg++ main.cpp -o &OUT&";
	} else {
		mainFilePath = pjgen::rootDirPath + "/src/main.cpp";
		makefileContent = 
R"(OUT := &OUT&
CC := g++
DIR_SRC := src
INC := -Isrc
CFLAGS := -std=c++17
SRC := $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
OBJ := $(patsubst %.cpp, %.o, $(SRC))

.PHONY: all clean

all: $(OBJ) $(OUT)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $@

clean:
	rm $(OBJ) $(OUT))";

		if(!std::filesystem::create_directory(pjgen::rootDirPath + "/src")) {
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, mainFileContent);

	return true;
}
