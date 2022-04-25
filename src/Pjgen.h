#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <list>

#include "ProjectTemplate.h"
#include "ColoredPrint.h"

namespace pjgen {
	extern std::string rootDirPath;
	extern std::vector<std::string> flags;
	extern std::string selectedTemplateName;

	void Init(int argc, const char **argv);
	void CreateRootDir(std::string &projectName);
	bool WriteToFile(std::string &path, std::string &content);
	void PrintHelp();
	void ReplaceAll(std::string &src, std::string toReplace, std::string replaceWith);
}
