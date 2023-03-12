#include "cppTemplate.h"
#include "runScript.h"
#include "templates/cpp/cppTemplateFiles.h"

bool CppTemplate::_Generate(std::string &projectName) const {
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
		mainFilePath = "main.cpp";
		makefileContent = CPP_TEMPLATE_MAKEFILE_SIMPLE_CONTENT;
	} else {
		mainFilePath =  "src/main.cpp";
		makefileContent = CPP_TEMPLATE_MAKEFILE_CONTENT;
		if(!std::filesystem::create_directory("src")) {
			ColoredPrintLine(RED, "Failed to create src directory");
			return false;
		}
	}

	pjgen::ReplaceAll(makefileContent, makefileContent, "&OUT&", projectName);

	pjgen::WriteToFile(makefilePath, makefileContent);
	pjgen::WriteToFile(mainFilePath, CPP_TEMPLATE_MAIN_FILE_CONTENT);

	CreateRunScript(projectName, !flagSimple);

	return true;
}
