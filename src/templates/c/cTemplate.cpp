#include "cTemplate.h"
#include "coloredPrint.h"
#include "runScript.h"
#include "templates/c/cTemplateFiles.h"

bool CTemplate::_Generate(std::string &projectName) const {
	bool flagSimple = false;
	for(std::string_view flag : pjgen::flags) {
		if(flag == "simple") {
			flagSimple = true;
			break;
		}
	}

	std::string mainFilePath;
	std::string makefilePath = "Makefile";
	std::string makefileContent;
	if(flagSimple) {
		mainFilePath = "main.c";
		makefileContent = C_TEMPLATE_MAKEFILE_SIMPLE_CONTENT;
	} else {
		mainFilePath = "src/main.c";
		makefileContent = C_TEMPLATE_MAKEFILE_CONTENT;

		if(!std::filesystem::create_directory("src")) {
			ColoredPrintLine(RED, "Failed to create src directory");
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, C_TEMPLATE_MAIN_FILE_CONTENT);

	CreateRunScript(projectName, !flagSimple);

	return true;
}
