#include "pjgen.h"
#include "pjgen_c.h"
#include "pjgen_web.h"

char *g_root_dir;
char *g_proj_name;
int *g_argc_p;
const char **g_argv_p;

static void create_root_folder();
static void print_help();

#define CUR_SET_X(x) "\r\033[" x "C"
#define HELP_TAB_SZ "20"

int main(int argc, const char **argv) {
        if(argc < 3) {
                print_help();
                return 1;
        }

        g_argc_p = &argc;
        g_argv_p = argv;

        const char *lang = argv[1];
	g_root_dir = malloc(PATH_SIZE);

        g_proj_name = malloc(sizeof(char) * strlen(argv[2]) + 1);
        strcpy(g_proj_name, argv[2]);
        
        create_root_folder();

        if(strcmp(lang, "c") == 0)              gen_c();
        else if(strcmp(lang, "cpp") == 0)       gen_cpp();
        else if(strcmp(lang, "web") == 0)       gen_web();

	free(g_root_dir);
        
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

static void print_help() {
        puts("pjgen ~ rxtthin");
        puts("---------------");
        puts("usage:" CUR_SET_X(HELP_TAB_SZ) "pjgen <lang> <proj name> <flags>");
        puts("<lang>:" CUR_SET_X(HELP_TAB_SZ) "c, cpp, web");
        puts("<proj name>:" CUR_SET_X(HELP_TAB_SZ) "Name of your project, remember to wrap the text with quotes if it has more than one word.");
        puts("<flags>:\n\t<C/C++>: [-s, --simple]");
}

void save_to_file(const char *path, const char *content) {
        FILE *file = fopen(path, "w");
        if(!file) {
                printf("Unable to open file '%s'.\n", path);
                return;
        }

        fputs(content, file);
        fclose(file);
}
