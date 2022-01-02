#include "pjgen.h"

#include "langs/cpp_c.h"
#include "langs/web.h"

static void create_root_folder();

int *g_argc_p;
const char **g_argv_p;
const char *g_proj_name;
char g_root_dir[PATH_SIZE];

int main(int argc, const char **argv) {
        if(argc < 2) {
		printf("Invalid parameters, type `pjgen --help` for help.");
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
        
        if(strcmp(lang, "c") == 0) {
		create_root_folder();
		gen_c();
	} else if(strcmp(lang, "cpp") == 0 || strcmp(lang, "c++") == 0 || strcmp(lang, "cc") == 0) {
		create_root_folder();
		gen_cpp();
	} else if(strcmp(lang, "web") == 0 || strcmp(lang, "html") == 0 || strcmp(lang, "css") == 0) { 
		create_root_folder();
		gen_web();
	} else {
		printf("Pjgen doesn't support language `%s`, type `pjgen --help` for help.\n", lang);
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
	puts("languages (name[tags]): C[c], C++[cc, cpp, c++], HTML/CSS[web, html, css]");
	puts("flags:");
	puts("\tC/C++:");
	puts("\t\t--simple, -s: Doesn't create the src directory and makes the Makefile much simpler.");
}

void save_to_file(const char *path, const char *content) {
        FILE *file = fopen(path, "w");
        if(!file) {
                perror("Unable to open file '%s'", path);
                return;
        }

        fputs(content, file);
        fclose(file);
}
