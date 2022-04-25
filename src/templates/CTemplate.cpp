#include "CTemplate.h"

constexpr std::string_view CTemplate::GetName() const {
	return "C";
}

bool CTemplate::_Generate(std::string &projectName) const {
	bool flagSimple = false;
	for(std::string flag : pjgen::flags) {
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
	std::string makefilePath = pjgen::rootDirPath + "/Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = pjgen::rootDirPath + "/main.c";
		makefileContent = "all:\n\tgcc main.c -o &OUT&";
	} else {
		mainFilePath = pjgen::rootDirPath + "/src/main.c";
		makefileContent = 
R"(OUT := &OUT&
CC := gcc
DIR_SRC := src
INC := -Isrc
CFLAGS := -std=gnu99
SRC := $(wildcard $(addsuffix /*.c, $(DIR_SRC)))
OBJ := $(patsubst %.c, %.o, $(SRC))

.PHONY: all

all: $(OBJ) $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $@

clean:
	rm *.o")";

		if(!std::filesystem::create_directory(pjgen::rootDirPath + "/src")) {
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, mainFileContent);

	return true;
}
