#include "PythonTemplate.h"

bool PythonTemplate::_Generate(std::string &projectName) const {
	std::string filePath = pjgen::rootDirPath + "/main.py";
	std::string_view fileContent = "print(\"hello world\")";

	if(!pjgen::WriteToFile(filePath, fileContent))
		return false;

	return true;
}
