#include "Pjgen.h"

#include "templates/PythonTemplate.h"
#include "templates/WebTemplate.h"
#include "templates/CTemplate.h"
#include "templates/CppTemplate.h"

// TODO: Decide whether std::list or std::vector should be used here.
std::pair<std::list<std::string>, ProjectTemplate*> templates[] {
	{{"c"}, new CTemplate()},
	{{"cpp", "cc" "c++"}, new CppTemplate()},
	{{"web", "html", "css"}, new WebTemplate()},
	{{"py", "python"}, new PythonTemplate()},
};

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

	std::string projectName = argv[2];
	std::string language = argv[1];
	std::transform(language.begin(), language.end(), language.begin(), tolower);

	for(std::pair<std::list<std::string>, ProjectTemplate*> pair : templates) {
		std::list<std::string> &aliases = pair.first;
		ProjectTemplate *projectTemplate = pair.second;

		for(std::string alias : aliases) {
			if(language == alias) {
				pjgen::CreateRootDir(projectName);
				if(projectTemplate->Generate(projectName)) {
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
