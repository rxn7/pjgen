#include "ColoredPrint.h"
#include "Pjgen.h"
#include <unistd.h>

#include "templates/python/PythonTemplate.h"
#include "templates/web/WebTemplate.h"
#include "templates/c/CTemplate.h"
#include "templates/cpp/CppTemplate.h"

static void InvalidArgsError();

int main(int argc, const char **argv) {
	std::pair<std::string, std::unique_ptr<ProjectTemplate>> templates[] {
		{"c", std::make_unique<CTemplate>()},
		{"cpp cc c++", std::make_unique<CppTemplate>()},
		{"web html css", std::make_unique<WebTemplate>()},
		{"py python", std::make_unique<PythonTemplate>()},
	};

	if(argc < 2)
		InvalidArgsError();

	if(strcmp(argv[1], "--help") == 0) {
		pjgen::PrintHelp();
		return 0;
	} else if(argc < 3)
		InvalidArgsError();

	pjgen::Init(argc, argv);

	std::string projectName = argv[2];
	std::string language = argv[1];
	std::transform(language.begin(), language.end(), language.begin(), tolower); // Convert user-entered language to lower case

	for(const auto &[aliases, templ] : templates) {
		std::stringstream aliasesSs(aliases);
		std::string alias;

		while(aliasesSs >> alias) {
			if(language == alias) {
				pjgen::CreateRootDir(projectName); 
				if(templ->Generate(projectName)) {
					ColoredPrintLine(GREEN, "Project '" << projectName << "' successfully generated!");
					exit(EXIT_SUCCESS);
				} else {
					ColoredPrintLine(RED, "Failed to generate project '" << projectName << "'.");
					exit(EXIT_FAILURE);
				}
				break;
			}
		}
	}

	ColoredPrintLine(RED, "Couldn't find template '" << language << "'.");
	return EXIT_FAILURE;
}

static void InvalidArgsError() {
	ColoredPrintLine(RED, "Invalid arguments, type `pjgen --help` for help.");
	exit(EXIT_FAILURE);
}