#include "pjgen.h"

#include "langs/cpp_c.h"
#include "langs/web.h"
#include "langs/py.h"

static void create_root_folder();

int *g_argc_p;
const char **g_argv_p;
const char *g_proj_name;
char g_root_dir[PATH_SIZE];

int main(int argc, const char **argv) {
        if(argc < 2) {
		printf("Invalid parameters, type `pjgen --help` for help.\n");
                return 1;
        }
	
	if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		print_help();
		return 0;
	}

        g_argc_p = &argc;
        g_argv_p = argv;
        g_proj_name = argv[2];
        char *lang = (char *) argv[1];

	#define lang_cmp(s) strcmp(lang, s) == 0

        if(lang_cmp("c")) {
		create_root_folder();
		gen_c();
	} else if(lang_cmp("cpp") || lang_cmp("c++") || lang_cmp("cc")) {
		create_root_folder();
		gen_cpp();
	} else if(lang_cmp("web") || lang_cmp("html") || lang_cmp("css")) { 
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
        char loc[PATH_SIZE];
        strcpy(loc, getenv("PWD"));
        strcat(loc, "/");
        strcat(loc, g_proj_name);

        DIR *dir = opendir(loc);
        closedir(dir);
        if(dir) {
                printf("Directory '%s' already exists!\n", loc);
                exit(EXIT_FAILURE);
        }

        printf("Project root location: %s\n", loc);
        mkdir(loc, 0700);
        
        strcpy(g_root_dir, loc);
}

void print_help() {
	puts("usage: pjgen <language tag> <project name> <(optional) flags>");
	puts("languages (name[tags]):");
	puts("\tC[c]");
	puts("\tC++[cc,cpp,c++]");
	puts("\tHTML/CSS[web,html,css]");
	puts("\tPython[py,python]");
	puts("flags:");
	puts("\tC/C++:");
	puts("\t\t--simple, -s: Doesn't create the src directory and makes the Makefile much simpler.");
}

void save_to_file(const char *path, const char *content) {
        FILE *file = fopen(path, "w");
        if(!file) {
                perror("Unable to open file");
                return;
        }

        fputs(content, file);
        fclose(file);
}
