#pragma once

#include "pjgen.h"
#include <stdbool.h>
#include <stdio.h>

static void save_makefile(const char *_compiler, const char *_lang, const char *_cflags, const char *_proj_name, bool _simple) {
        #define MAKEFILE_SIMPLE \
                "all:\n" \
                "       %s main.c -o %s\n" \

	#define MAKEFILE \
		"SRCS = -c src/*.%s\n" \
		"HDRS = -Isrc\n" \
		"CFLAGS = %s\n" \
		"OBJS = main.o\n" \
		"\n" \
		"all: compile link clean\n" \
		"\n" \
		"compile:\n" \
		"	%s $(SRCS) $(HDRS) $(CFLAGS)\n" \
		"\n" \
		"link:\n" \
		"	%s $(OBJS) $(LIBS) -o %s\n" \
		"\n" \
		"clean:\n" \
		"	rm *.o"

	char content[4096];

        if(_simple) {
                sprintf(content, MAKEFILE_SIMPLE, _compiler, _proj_name);
        } else {
                sprintf(content, MAKEFILE, _lang, _cflags, _compiler, _compiler, _proj_name);
        }

	char path[PATH_SIZE];
        strcpy(path, g_cwd); 
        strcat(path, "/Makefile");

	save_to_file(path, content);
}

static void save_main(bool _is_cpp /* is it C or C++ file? */, const char *_src_file_name, bool _simple) {
	#define MAIN_C \
		"#include <stdio.h>\n\n" \
		"int main(int argc, const char **argv) {\n" \
		"	printf(\"Hello, World!\");\n" \
		"}"

	#define MAIN_CPP \
		"#include <iostream>\n\n" \
		"int main(int argc, const char **argv) {\n" \
		"	std::cout << \"Hello, World!\" << std::endl;\n" \
		"}"

        char src_file_path[PATH_SIZE];
        if(_simple) {
                strcpy(src_file_path, g_cwd);
                strcat(src_file_path, _src_file_name);
        } else {
                char src_dir_path[PATH_SIZE];
                strcpy(src_dir_path, g_cwd);
                strcat(src_dir_path, "/src");
                mkdir(src_dir_path, 0777);

                strcpy(src_file_path, src_dir_path);
                strcat(src_file_path, "/");
                strcat(src_file_path, _src_file_name);
        }

        char src_file_content[4096];
        sprintf(src_file_content, _is_cpp ? MAIN_CPP : MAIN_C);

	save_to_file(src_file_path, src_file_content);
} 

GEN_PROJECT(c) {
        /* TODO: Check if -s or --simple argument is passed. */
        save_main(false, "main.c", false);
        save_makefile("gcc", "c", "-std=gnu99", _name, false);
}

GEN_PROJECT(cpp) {
        /* TODO: Check if -s or --simple argument is passed. */
        save_main(false, "main.cpp", false);
        save_makefile("g++", "cpp", "-std=c++17", _name, false);
}
