#include "pythonTemplate.h"
#include "templates/python/pythonTemplateFiles.h"

bool PythonTemplate::_Generate(std::string &projectName) const {
	std::string filePath = "main.py";

	if(!pjgen::WriteToFile(filePath, PYTHON_TEMPLATE_MAIN_FILE_CONTENT))
		return false;

	return true;
}
