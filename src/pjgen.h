#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <sys/stat.h>

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;

#define PATH_SIZE 4096

extern char g_cwd[]; /* Declared in pjtmp.c. */

void save_to_file(const char *_path, const char *_content);

#define GEN_PROJECT(lang) void gen_##lang(const char *_name, i32 _argc, const char *_args)
