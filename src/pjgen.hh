#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <filesystem>

extern int g_argc;
extern const char **g_argv;
extern const char *g_proj_name;
extern std::string g_root_dir;

void save_to_file(std::string &path, std::string &content);
void print_help();
void replace_all(std::string &s, std::string to_replace, std::string replace_with);

#define FOR_EACH_FLAG() for(unsigned int i=3; i<g_argc; ++i) 
