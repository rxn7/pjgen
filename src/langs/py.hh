#pragma once

#include "../pjgen.hh"
#define MAIN_PY "print(\"hello world\")"

void gen_py() {
	std::string path = g_root_dir + "/main.py";

	std::string content = MAIN_PY;
	save_to_file(path, content);

	puts("Successfully generated a python project.");
}
