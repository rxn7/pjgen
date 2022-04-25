#include "PythonTemplate.h"

#define MAIN_PY_CONTENT "print(\"hello world\")"

constexpr std::string_view PythonTemplate::GetName() const {
	return "Python";
}

bool PythonTemplate::_Generate(std::string &projectName) const {
	std::string filePath = pjgen::rootDirPath + "/main.py";
	std::string fileContent = MAIN_PY_CONTENT;

	if(!pjgen::WriteToFile(filePath, fileContent)) {
		return false;
	}

	return true;
}
