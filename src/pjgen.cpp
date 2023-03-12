#include "pjgen.h" 
#include "coloredPrint.h"
#include <fstream>
#include <unistd.h>

std::vector<std::string_view> pjgen::flags;

void pjgen::Init(int argc, const char **argv) {
	for(int i=3; i<argc; ++i) {
		std::string_view flag = argv[i];
		if(flag.starts_with("--"))
			pjgen::flags.push_back({flag.begin() + 2, flag.length() - 2});
	}
}

void pjgen::CreateRootDir(const std::string &projectName) {
	std::filesystem::path path = std::string(getenv("PWD")) + "/" + projectName;

	if(std::filesystem::exists(path)) {
		ColoredPrintLine(RED, "Directory " << path.string() << " already exists!");
		exit(EXIT_FAILURE);
	}

	std::filesystem::create_directory(path);
	std::cout << "Root directory: " << path << "\n";
	chdir(path.c_str());
}

bool pjgen::WriteToFile(const std::string &path, std::string_view content) {
	std::ofstream stream;
	stream.open(path);

	if(!stream.is_open())
		return false;

	stream << content;
	stream.close();

	return true;
}

void pjgen::PrintHelp() {
	puts("Usage: pjgen <language tag> <project name> <(optional) flags>");
	puts("Languages (name[tags]):");
	puts("  C[c] [--simple]");
	puts("  C++[cc,cpp,c++] [--simple]");
	puts("  HTML/CSS[web,html,css] [--js]");
	puts("  Python[py,python]");
}

void pjgen::ReplaceAll(const std::string &src, std::string &dest, std::string_view toReplace, std::string_view replaceWith) {
	std::ostringstream oss;
	std::size_t pos = 0;
	std::size_t prevPos = 0;

	for(;;) {
		prevPos = pos;

		pos = src.find(toReplace, pos);
		if(pos == std::string::npos)
			break;

		oss << src.substr(prevPos, pos - prevPos);
		oss << replaceWith;
		pos += toReplace.size();
	}

	oss << src.substr(prevPos);
	dest = oss.str();
}
