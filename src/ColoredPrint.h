#pragma once

#define BLACK "\e[0;30m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define CYAN "\e[0;36m"
#define WHITE "\e[0;37m"

#include <iostream>

// TODO: Windows colored output

#if __has_include(<unistd.h>)
	#define ColoredPrintLine(color, msg) std::cout << color << msg << WHITE << std::endl;
#else
	#define ColoredPrintLine(color, msg) std::cout << msg << std::endl;
#endif
