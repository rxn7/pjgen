#pragma once

#include <string.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

namespace pjgen {
	extern std::string rootDirPath;
	extern std::vector<std::string> flags;

	void Init(int argc, const char **argv);
	void CreateRootDir(std::string &projectName);
	bool WriteToFile(std::string &path, std::string &content);
	void PrintHelp();
	void ReplaceAll(std::string &src, std::string toReplace, std::string replaceWith);
}
