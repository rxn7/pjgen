#include "CppTemplate.h"
#include "Pjgen.h"

#define MAIN_CPP_CONTENT \
	"#include <iostream>\n\n" \
	"int main(int argc, const char **argv) {\n" \
	"	std::cout << \"Hello, World!\";\n" \
	"}"

#define MAKEFILE_SIMPLE \
	"all:\n" \
	"\tg++ main.cpp -o &OUT&\n" \

#define MAKEFILE \
	"SRCS := -c src/*.cpp\n" \
	"HDRS := -Isrc\n" \
	"CFLAGS := -std=c++17\n" \
	"OBJS := main.o\n" \
	"\n" \
	"all: compile link clean\n" \
	"\n" \
	"compile:\n" \
	"\tg++ $(SRCS) $(HDRS) $(CFLAGS)\n" \
	"\n" \
	"link:\n" \
	"\tg++ $(OBJS) $(LDFLAGS) -o &OUT&\n" \
	"\n" \
	"clean:\n" \
	"\trm *.o"

CppTemplate::CppTemplate() : ProjectTemplate("C++") { }

bool CppTemplate::_Generate(std::string &projectName) {
	bool flagSimple = false;
	for(std::string flag : pjgen::flags) {
		if(flag == "simple") {
			flagSimple = true;
			break;
		}
	}

	std::string mainFileContent = MAIN_CPP_CONTENT;
	std::string mainFilePath;
	std::string makefilePath = pjgen::rootDirPath + "/Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = pjgen::rootDirPath + "/main.cpp";
		makefileContent = MAKEFILE_SIMPLE;
	} else {
		mainFilePath = pjgen::rootDirPath + "/src/main.cpp";
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
