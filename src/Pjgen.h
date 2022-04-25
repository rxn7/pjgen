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

	void PrintHelp();
	void Init(int argc, const char **argv);
	void CreateRootDir(const std::string &projectName);
	bool WriteToFile(const std::string &path, std::string_view content);
	void ReplaceAll(const std::string &src, std::string &dest, std::string_view toReplace, std::string_view replaceWith);
}
