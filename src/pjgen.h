#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <sys/stat.h>

#define PATH_SIZE 4096

extern char g_cwd[]; /* Declared in pjtmp.c. */

void save_to_file(const char *path, const char *content);

#define GEN_PROJECT(lang) void gen_##lang(const char *name, int argc, const char *args)
