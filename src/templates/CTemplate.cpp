#include "CTemplate.h"
#include "Pjgen.h"
#include <filesystem>

#define MAIN_C_CONTENT \
	"#include <stdio.h>\n\n" \
	"int main(int argc, const char **argv) {\n" \
	"\tprintf(\"Hello, World!\");\n" \
	"}"

#define MAKEFILE_SIMPLE \
	"all:\n" \
	"\tgcc main.c -o &OUT&\n" \

#define MAKEFILE \
	"SRCS := -c src/*.c\n" \
	"HDRS := -Isrc\n" \
	"CFLAGS := -std=gnu99\n" \
	"OBJS := main.o\n" \
	"\n" \
	"all: compile link clean\n" \
	"\n" \
	"compile:\n" \
	"\tgcc $(SRCS) $(HDRS) $(CFLAGS)\n" \
	"\n" \
	"link:\n" \
	"\tgcc $(OBJS) $(LDFLAGS) -o &OUT&\n" \
	"\n" \
	"clean:\n" \
	"\trm *.o"

CTemplate::CTemplate() : ProjectTemplate("C") { }

bool CTemplate::_Generate(std::string &projectName) {
	bool flagSimple = false;
	for(std::string flag : pjgen::flags) {
		if(flag == "simple") {
			flagSimple = true;
			break;
		}
	}

	std::string mainFileContent = MAIN_C_CONTENT;
	std::string mainFilePath;
	std::string makefilePath = pjgen::rootDirPath + "/Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = pjgen::rootDirPath + "/main.c";
		makefileContent = MAKEFILE_SIMPLE;
	} else {
		mainFilePath = pjgen::rootDirPath + "/src/main.c";
		makefileContent = MAKEFILE;

		if(!std::filesystem::create_directory(pjgen::rootDirPath + "/src")) {
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, mainFileContent);

	return true;
}
