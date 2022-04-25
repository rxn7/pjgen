#include "Pjgen.h"
#include "ProjectTemplate.h"
#include "ColoredPrint.h"

#include <array>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include "templates/PythonTemplate.h"
#include "templates/WebTemplate.h"
#include "templates/CTemplate.h"
// #include "templates/CppTemplate.h"

int main(int argc, const char **argv) {
        if(argc < 2) {
		printf("Invalid arguments, type `pjgen --help` for help.\n");
		exit(EXIT_FAILURE);
        }

	if(strcmp(argv[1], "--help") == 0) {
		pjgen::PrintHelp();
		exit(EXIT_FAILURE);
	}

	pjgen::Init(argc, argv);

	ProjectTemplate *projectTemplate = nullptr;
	std::string language = argv[1];
	std::transform(language.begin(), language.end(), language.begin(), tolower);

	std::string projectName = argv[2];

	if(language == "c") projectTemplate = new CTemplate();
	// else if(language == "cpp" || language == "cc" || language == "c++") projectTemplate = new CppTemplate();
	else if(language == "web" || language == "html" || language == "js") projectTemplate = new WebTemplate();
	else if(language == "py" || language == "python") projectTemplate = new PythonTemplate();

	if(projectTemplate != nullptr) {
		pjgen::CreateRootDir(projectName);
	 	if(projectTemplate->Generate(projectName)) {
			ColoredPrintLine(GREEN, "Project '" << projectName << "' successfully generated!");
		} else {
			ColoredPrintLine(RED, "Failed to generate project '" << projectName << "'.");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
