#pragma once

#include "pjgen.h"
#define MAIN_PY "print(\"hello world\")"

void gen_py() {
	char path[PATH_SIZE];
	strcpy(path, g_root_dir);
	strcat(path, "/main.py");
	save_to_file(path, MAIN_PY);
}
