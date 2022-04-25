#include "PythonTemplate.h"

#define MAIN_PY_CONTENT "print(\"hello world\")"

PythonTemplate::PythonTemplate() : ProjectTemplate("Python") { }

bool PythonTemplate::_Generate(std::string &projectName) {
	std::string filePath = pjgen::rootDirPath + "/main.py";
	std::string fileContent = MAIN_PY_CONTENT;

	if(!pjgen::WriteToFile(filePath, fileContent)) {
		return false;
	}

	return true;
}
