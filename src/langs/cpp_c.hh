#pragma once

#include "../pjgen.hh"

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
	"\t&CC& main.&LANG& -o &OUT&\n" \

#define MAKEFILE \
	"SRCS = -c src/*.&LANG&\n" \
	"HDRS = -Isrc\n" \
	"CFLAGS = &CFLAGS&\n" \
	"OBJS = main.o\n" \
	"\n" \
	"all: compile link clean\n" \
	"\n" \
	"compile:\n" \
	"\t&CC& $(SRCS) $(HDRS) $(CFLAGS)\n" \
	"\n" \
	"link:\n" \
	"\t&CC& $(OBJS) $(LIBS) -o &OUT&\n" \
	"\n" \
	"clean:\n" \
	"\trm *.o"

static bool flag_simple = false;

static void check_flags() {
        FOR_EACH_FLAG() {
                if(strcmp(g_argv[i], "-s") == 0 || strcmp(g_argv[i], "--simple") == 0) {
                        flag_simple = true;        
                } else {
                        fprintf(stderr, "Unknown flag for C/C++ project: '%s'.\n", g_argv[i]);
                }
        }
}

static void save_makefile(const char *compiler, const char *lang, const char *cflags) {
	/* FIXME: This is terrible */
	std::string content;

	if(flag_simple) {
		content = MAKEFILE_SIMPLE;
		replace_all(content, "&CC&", compiler);
		replace_all(content, "&LANG&", lang);
		replace_all(content, "&OUT&", g_proj_name);
	} else {
		content = MAKEFILE;
		replace_all(content, "&CFLAGS&", cflags);
		replace_all(content, "&CC&", compiler);
		replace_all(content, "&LANG&", lang);
		replace_all(content, "&OUT&", g_proj_name);
	}

	std::string path = g_root_dir + "/Makefile";
	save_to_file(path, content);
}

static void save_main(bool is_cpp, const char *src_file_name) {
	std::string src_path;

	if(flag_simple) {
                src_path = g_root_dir + "/" + src_file_name;
        } else {
		std::string dir_path = g_root_dir + "/src";
                mkdir(dir_path.c_str(), 0777);

                src_path = dir_path + "/" + src_file_name;
        }

	std::string src_file_content = is_cpp ? MAIN_CPP : MAIN_C;
	save_to_file(src_path, src_file_content);
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
