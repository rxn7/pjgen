#pragma once

#include "pjgen.h"

#define MAIN_C \
	"#include <stdio.h>\n\n" \
	"int main(int argc, const char **argv) {\n" \
	"\tprintf(\"Hello, World!\");\n" \
	"}"

#define MAIN_CPP \
	"#include <iostream>\n\n" \
	"int main(int argc, const char **argv) {\n" \
	"\tstd::cout << \"Hello, World!\" << std::endl;\n" \
	"}"

#define MAKEFILE_SIMPLE \
	"all:\n" \
	"\t%s main.%s -o %s\n" \

#define MAKEFILE \
	"SRCS = -c src/*.%s\n" \
	"HDRS = -Isrc\n" \
	"CFLAGS = %s\n" \
	"OBJS = main.o\n" \
	"\n" \
	"all: compile link clean\n" \
	"\n" \
	"compile:\n" \
	"\t%s $(SRCS) $(HDRS) $(CFLAGS)\n" \
	"\n" \
	"link:\n" \
	"\t%s $(OBJS) $(LIBS) -o %s\n" \
	"\n" \
	"clean:\n" \
	"\trm *.o"

static bool f_simple = false;

static void check_flags() {
        FOR_EACH_FLAG() {
                if(strcmp(g_argv_p[i], "-s") == 0 || strcmp(g_argv_p[i], "--simple") == 0) {
                        f_simple = true;        
                } else {
                        fprintf(stderr, "Unknown flag for C/C++ project: '%s'.\n", g_argv_p[i]);
                }
        }
}

static void save_makefile(const char *compiler, const char *lang, const char *cflags) {
	/* FIXME: This is terrible */
	char content[4096];
        if(f_simple) sprintf(content, MAKEFILE_SIMPLE, compiler, lang, g_proj_name);
        else sprintf(content, MAKEFILE, lang, cflags, compiler, compiler, g_proj_name);

	char path[PATH_SIZE];
        strcpy(path, g_root_dir); 
        strcat(path, "/Makefile");

	save_to_file(path, content);
}

static void save_main(bool is_cpp, const char *src_file_name) {
        char src_file_path[PATH_SIZE];

        if(f_simple) {
                strcpy(src_file_path, g_root_dir);
                strcat(src_file_path, "/");
                strcat(src_file_path, src_file_name);
        } else {
                char src_dir_path[PATH_SIZE];
                strcpy(src_dir_path, g_root_dir);
                strcat(src_dir_path, "/src");
                mkdir(src_dir_path, 0777);

                strcpy(src_file_path, src_dir_path);
                strcat(src_file_path, "/");
                strcat(src_file_path, src_file_name);
        }

        char src_file_content[4096];
        sprintf(src_file_content, is_cpp ? MAIN_CPP : MAIN_C);

	save_to_file(src_file_path, src_file_content);
} 

void gen_c() {
        check_flags();
        save_main(false, "main.c");
        save_makefile("gcc", "c", "-std=gnu99");
}

void gen_cpp() {
        check_flags();
        save_main(true, "main.cpp");
        save_makefile("g++", "cpp", "-std=c++17");
}
