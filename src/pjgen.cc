#include "pjgen.hh"
#include "langs/cpp_c.hh"
#include "langs/web.hh"
#include "langs/py.hh"

#include <filesystem>
#include <sstream>

#define lang_cmp(s) (strcmp(lang, s) == 0)

static void create_root_folder();

int g_argc;
const char **g_argv;
const char *g_proj_name;
std::string g_root_dir;

int main(int argc, const char **argv) {
        if(argc < 2) {
		printf("Invalid parameters, type `pjgen --help` for help.\n");
                return 1;
        }
	
	if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		print_help();
		return 0;
	}

        g_argc = argc;
        g_argv = argv;
        g_proj_name = argv[2];
        char *lang = (char *)argv[1];

        if(lang_cmp("c")) {
		create_root_folder();
		gen_c();
	} else if(lang_cmp("cpp") || lang_cmp("c++") || lang_cmp("cc")) {
		create_root_folder();
		gen_cpp(); } else if(lang_cmp("web") || lang_cmp("html") || lang_cmp("css")) { 
		create_root_folder();
		gen_web();
	} else if(lang_cmp("py") || lang_cmp("python")) {
		create_root_folder();		
		gen_py();
	} else {
		printf("Pjgen doesn't support language `%s`, type `pjgen --help` for help.\n", lang);
		return 1;
	}

	return 0;
}

static void create_root_folder() {
	std::filesystem::path path = std::string(getenv("PWD")) + "/" + g_proj_name;

	if(std::filesystem::exists(path)) {
		std::cout << "Directory " << path << " already exists!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::filesystem::create_directory(path);

	std::cout << "Root directory: " << path << std::endl;

	g_root_dir = path;
}

void print_help() {
	puts("Usage: pjgen <language tag> <project name> <(optional) flags>");
	puts("Languages (name[tags]):");
	puts("\tC[c]");
	puts("\tC++[cc,cpp,c++]");
	puts("\tHTML/CSS[web,html,css]");
	puts("\tPython[py,python]");
	puts("Flags:");
	puts("\tC/C++:");
	puts("\t\t--simple, -s: Doesn't create the src directory and makes the Makefile much simpler.");
}

void save_to_file(std::string &path, std::string &content) {
        FILE *file = fopen(path.c_str(), "w");
        if(!file) {
		std::cout << "Failed to open file: '" << path << "'!" << std::endl;
                return;
        }

        fputs(content.c_str(), file);
        fclose(file);
}

void replace_all(std::string &s, std::string to_replace, std::string replace_with) {
	std::ostringstream oss;
	std::size_t pos = 0;
	std::size_t prev_pos = 0;

	for(;;) {
		prev_pos = pos;
		pos = s.find(to_replace, pos);
		if(pos == std::string::npos) {
			break;
		}
		oss << s.substr(prev_pos, pos - prev_pos);
		oss << replace_with;
		pos += to_replace.size();
	}

	oss << s.substr(prev_pos);
	s = oss.str();
}
