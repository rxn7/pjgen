#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <dirent.h>
#include <sys/stat.h>

#define PATH_SIZE 4096

extern char *g_root_dir;
extern char *g_proj_name;
extern int *g_argc_p;
extern const char **g_argv_p;

void save_to_file(const char *path, const char *content);

#define GEN_PROJECT(lang) void gen_##lang()
#define FOR_EACH_FLAG() for(unsigned int i=3; i<*g_argc_p; ++i) 
