#include "Pjgen.h"
#include "ColoredPrint.h"
#include <fstream>

std::string pjgen::rootDirPath;
std::vector<std::string> pjgen::flags;

void pjgen::Init(int argc, const char **argv) {
	for(int i=3; i<argc; ++i) {
		std::string flag = argv[i];
		if(flag.starts_with("--")) {
			pjgen::flags.push_back(flag.substr(2));
		}
	}
}

void pjgen::CreateRootDir(const std::string &projectName) {
	std::filesystem::path path = std::string(getenv("PWD")) + "/" + projectName;

	if(std::filesystem::exists(path)) {
		ColoredPrintLine(RED, "Directory " << path.string() << " already exists!");
		exit(EXIT_FAILURE);
	}

	std::filesystem::create_directory(path);
	std::cout << "Root directory: " << path << std::endl;
	rootDirPath = path.string();
}

bool pjgen::WriteToFile(const std::string &path, std::string_view content) {
	std::ofstream stream;
	stream.open(path);

	if(!stream.is_open()) {
		return false;
	}

	stream << content;
	stream.close();

	return true;
}

void pjgen::PrintHelp() {
	puts("Usage: pjgen <language tag> <project name> <(optional) flags>");
	puts("Languages (name[tags]):");
	puts("\tC[c]");
	puts("\tC++[cc,cpp,c++]");
	puts("\tHTML/CSS[web,html,css]");
	puts("\tPython[py,python]");
	puts("Flags:");
	puts("\tC/C++:");
	puts("\t\t--simple: Good for single-file projects.");
}

void pjgen::ReplaceAll(const std::string &src, std::string &dest, std::string_view toReplace, std::string_view replaceWith) {
	std::ostringstream oss;
	std::size_t pos = 0;
	std::size_t prevPos = 0;

	for(;;) {
		prevPos = pos;
		pos = src.find(toReplace, pos);
		if(pos == std::string::npos) {
			break;
		}
		oss << src.substr(prevPos, pos - prevPos);
		oss << replaceWith;
		pos += toReplace.size();
	}

	oss << src.substr(prevPos);
	dest = oss.str();
}
