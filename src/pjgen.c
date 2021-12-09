#include <stdio.h>

#include "pjgen.h"
#include "pjgen_c.h"
#include "pjgen_web.h"

char g_cwd[PATH_SIZE];

static void create_root_folder(const char *name);

int main(int argc, const char **argv) {
        if(argc < 3) {
                puts("Visit https://github.com/rotth/pjtmp for help.");
                return 1;
        }

        getcwd(g_cwd, PATH_SIZE);

        const char *lang = argv[1];
        const char *name = argv[2];

        create_root_folder(name);

        if(strcmp(lang, "c") == 0) {
                gen_c(name, 0, 0);
        } else if(strcmp(lang, "cpp") == 0) {
                gen_cpp(name, 0, 0);
        } else if(strcmp(lang, "web") == 0) {
                gen_web(name, 0, 0);
        }
        
        return 0;
}

        char loc[PATH_SIZE];
        static void create_root_folder(const char *name) {
        strcpy(loc, g_cwd);
        strcat(loc, "/");
        strcat(loc, name);

        printf("Project root location: %s\n", loc);

        mkdir(loc, 0700);
        
        strcpy(g_cwd, loc);
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
