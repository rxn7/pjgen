#include "Pjgen.h"

#include "templates/PythonTemplate.h"
#include "templates/WebTemplate.h"
#include "templates/CTemplate.h"
#include "templates/CppTemplate.h"

// TODO: Decide whether std::list or std::vector should be used here.
std::pair<std::list<std::string>, std::unique_ptr<ProjectTemplate>> templates[] {
	{{"c"}, std::make_unique<CTemplate>()},
	{{"cpp", "cc" "c++"}, std::make_unique<CppTemplate>()},
	{{"web", "html", "css"}, std::make_unique<WebTemplate>()},
	{{"py", "python"}, std::make_unique<PythonTemplate>()},
};

int main(int argc, const char **argv) {
        if(argc < 2) {
		printf("Invalid arguments, type `pjgen --help` for help.\n");
		exit(EXIT_FAILURE);
        }

	if(strcmp(argv[1], "--help") == 0) {
		pjgen::PrintHelp();
		exit(EXIT_FAILURE);
	} else if(argc < 3) {
		printf("Invalid arguments, type `pjgen --help` for help.\n");
		exit(EXIT_FAILURE);
	}

	pjgen::Init(argc, argv);

	std::string projectName = argv[2];
	std::string language = argv[1];
	std::transform(language.begin(), language.end(), language.begin(), tolower);

	for(auto &pair : templates) {
		std::list<std::string> &aliases = pair.first;

		for(std::string alias : aliases) {
			if(language == alias) {
				pjgen::CreateRootDir(projectName);
				if(pair.second->Generate(projectName)) {
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
